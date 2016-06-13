
#include "BufferQueue.h"
#include "VideoBuffer.h"

#include <memory>
#include <mutex>
#include <cmath>

namespace AwMirrorOp {

BufferQueue::BufferQueue() :
    _mbInited(false),
    _mAccumulatedCount(0),
    _mFirstBuffer(nullptr),
    _mLastBuffer(nullptr),
    _mFirstFreeBuffer(nullptr),
    _mLastFreeBuffer(nullptr)
{

}

BufferQueue::~BufferQueue()
{
    _mFirstBuffer = nullptr;
    _mLastBuffer = nullptr;
    _mFirstFreeBuffer = nullptr;
    _mLastFreeBuffer = nullptr;
    _mbInited = false;
}

status_t BufferQueue::init(MediaType type, const uint16_t count, const uint32_t buffer_capacity)
{
    return _preAllocateBufferPools(type, count, buffer_capacity);
}

status_t BufferQueue::initCheck() const
{
    if (_mbInited == false) return NO_INIT;
    return NO_ERROR;
}


status_t BufferQueue::dequeueBuffer(BufferItemPtr &buffer)
{
    std::lock_guard<std::mutex> lock(_mMutex);
    if (_mFirstFreeBuffer == nullptr) {
        buffer = nullptr;
        return NO_BUFFER;
    }
    buffer = _mFirstFreeBuffer;
    buffer->setState(BufferItem::DEQUEUED);
    _mFirstFreeBuffer = _mFirstFreeBuffer->nextBufferItem();
    return OK;
}

status_t BufferQueue::queueBuffer(BufferItemPtr &buffer)
{
    std::lock_guard<std::mutex> lock(_mMutex);
    buffer->setState(BufferItem::QUEUED);
    buffer->buffer()->_setSerialNumber(++_mAccumulatedCount);
    _addBuffer(buffer);
    return OK;
}

status_t BufferQueue::acquireBuffer(BufferItemPtr &buffer)
{
    std::lock_guard<std::mutex> lock(_mMutex);
    if (_mFirstBuffer == nullptr) return NO_BUFFER;
    buffer = _mFirstBuffer;
    buffer->setState(BufferItem::ACQUIRED);
    _mFirstBuffer = _mFirstBuffer->nextBufferItem();
    if (_mFirstBuffer == nullptr) _mLastBuffer = nullptr;
    return OK;
}

status_t BufferQueue::releaseBuffer(BufferItemPtr &buffer)
{
    std::lock_guard<std::mutex> lock(_mMutex);
    buffer->setState(BufferItem::FREE);
    VideoBufferPtr videoBuffer = std::dynamic_pointer_cast<VideoBuffer>(buffer->buffer());
    if (videoBuffer != nullptr) {
        videoBuffer->setIFrame(false);
    }
    buffer->setNextBufferItem(nullptr);
    _mLastFreeBuffer->setNextBufferItem(buffer);
    if (_mFirstFreeBuffer == nullptr) _mFirstFreeBuffer = _mLastFreeBuffer;
    _mLastFreeBuffer = buffer;
    return OK;
}

//============= private functions ================================//

status_t BufferQueue::_preAllocateBufferPools(MediaType type, const uint16_t count, const uint32_t buffer_capacity)
{
    uint16_t _count = (uint16_t) count;
    uint8_t bigBufCount = 0;
    uint32_t sizeOfBigBuf = 0;
    if (type == VIDEO) {
        bigBufCount = (uint8_t) ceil(((float)count)/8);
        sizeOfBigBuf = buffer_capacity < (1<<18) ? (1<<18) : buffer_capacity; // (1<<18) = 256*1024 bytes
    }
    int i = 0;
    BufferItemPtr item = nullptr;
    uint32_t capacity = buffer_capacity;
    for (i = 0; i < count; ++i) {
        if (i < bigBufCount) {
            capacity = sizeOfBigBuf;
        } else {
            capacity = buffer_capacity;
        }

        if	(_mFirstFreeBuffer == nullptr) {
            item = _createBufferItem(type, capacity);
            _mFirstFreeBuffer = item;
        } else {
            item->setNextBufferItem(_createBufferItem(type, capacity));
            item = item->nextBufferItem();
        }
    }
    item->setNextBufferItem(nullptr);
    _mLastFreeBuffer = item;
    _mbInited = true;
    _mAccumulatedCount = 0;
    return OK;
}

BufferItemPtr BufferQueue::_createBufferItem(MediaType type, const uint32_t buffer_capacity)
{
    MediaBufferPtr buffer;
    if (type == VIDEO) {
        buffer = (MediaBufferPtr) (VideoBuffer::createBuffer(buffer_capacity, VideoFormat::H264));
    } else if (type == AUDIO) {
        //buffer = (MediaBufferPtr) (AudioBuffer::createBuffer(buffer_capacity, AudioFormat::PCM));
    } else {
        return nullptr;
    }
    BufferItemPtr item = std::make_shared<BufferItem>(buffer);
    return item;
}

void BufferQueue::_addBuffer(BufferItemPtr &buffer)
{
    if (_mFirstBuffer == nullptr) {
        _mFirstBuffer = buffer;
        _mLastBuffer = _mFirstBuffer;
    } else {
        _mLastBuffer->setNextBufferItem(buffer);
        _mLastBuffer = buffer;
    }
}

}
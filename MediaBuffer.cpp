#include "MediaBuffer.h"

#include "BufferItem.h"
#include <memory>
#include <cstring>

namespace AwMirrorOp {

MediaBuffer::MediaBuffer(const uint32_t capacity, const MediaType type) :
    _mData(malloc(capacity)),
    _mType(type),
    _mCapacity(capacity),
    _mSize(0),
    _mSN(0)
{
}

MediaBuffer::~MediaBuffer()
{
    if (_mData != nullptr) {
        free(_mData);
        _mData = nullptr;
    }
}

status_t MediaBuffer::copyData(void * data, const uint32_t size)
{
    status_t ret = NO_ERROR;
    if (data == nullptr) return INVALID_OPERATION;
    if (size > _mCapacity) {
        if ((ret = _reallocate(size)) != NO_ERROR) return ret;
    }
    std::memcpy(_mData, data, size);
    _mSize = size;
    return NO_ERROR;
}

status_t MediaBuffer::setDataSize(const uint32_t size)
{
    if (size > _mCapacity) return INVALID_OPERATION;
    _mSize = size;
    return NO_ERROR;
}

void * MediaBuffer::data() const
{
    return _mData;
}

MediaType MediaBuffer::type() const
{
    return _mType;
}

uint32_t MediaBuffer::capacity() const
{
    return _mCapacity;
}

uint32_t MediaBuffer::size() const
{
    return _mSize;
}

uint64_t MediaBuffer::serialnumber()
{
    return _mSN;
}

std::shared_ptr<BufferItem> MediaBuffer::getBox()
{
    auto box = _mBox.lock();
    return box;
}

// ================ private functions =================== //

void MediaBuffer::setBox(std::shared_ptr<BufferItem> box)
{
    _mBox = box;
}

status_t MediaBuffer::_reallocate(const uint32_t capacity)
{
    if (_mData != nullptr) {
        free(_mData);
    }
    _mData = malloc(capacity);
    if (_mData == nullptr) {
        return NO_MEMORY;
    }
    _mCapacity = capacity;
    _mSize = 0;
    _mSN = 0;
    return NO_ERROR;
}

void MediaBuffer::_setSerialNumber(uint64_t sn)
{
    _mSN = sn;
}

} // namespace AwMirrorOp

#include "BufferItem.h"
#include "VideoBuffer.h"

namespace AwMirrorOp {

BufferItemPtr BufferItem::createBufferItem(MediaType type, const uint32_t buffer_capacity)
{
    MediaBufferPtr buffer;
    if (type == VIDEO) {
		buffer = (MediaBufferPtr)(VideoBuffer::createBuffer(buffer_capacity, VideoFormat::H264));
	}
	else if (type == AUDIO) {
		//buffer = (MediaBufferPtr) (AudioBuffer::createBuffer(buffer_capacity, AudioFormat::PCM));
	}
	else {
		return nullptr;
	}
	BufferItemPtr item = std::make_shared<BufferItem>(buffer);
    buffer->setBox(item);
	return item;
}

BufferItem::BufferItem(MediaBufferPtr buffer) :
    _mBuffer(buffer),
    _mState(FREE),
    _mSlot(-1),
    _mNextItem(nullptr)
{
}

BufferItem::~BufferItem()
{
    _mBuffer = nullptr;
    _mState = FREE;
    _mSlot = -1;
    _mNextItem = nullptr;
}

MediaBufferPtr BufferItem::buffer() const
{
    return _mBuffer;
}

void BufferItem::setState(BufferItem::BufferState state)
{
    _mState = state;
}

BufferItem::BufferState BufferItem::state() const
{
    return _mState;
}

void BufferItem::setSlot(int32_t num)
{
    _mSlot = num;
}

int32_t BufferItem::slot() const
{
    return _mSlot;
}

//========== private functions ===============//
void BufferItem::setNextBufferItem(BufferItemPtr item)
{
    _mNextItem = item;
}

BufferItemPtr BufferItem::nextBufferItem() const
{
    return _mNextItem;
}

} // namespace AwMirrorOp

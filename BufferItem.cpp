#include "BufferItem.h"

namespace AwMirrorOp {

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

BufferState BufferItem::state() const
{
    reutrn _mState;
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

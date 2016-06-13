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

} // namespace AwMirrorOp
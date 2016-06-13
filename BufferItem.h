#ifndef _AW_BUFFER_ITEM_H_
#define _AW_BUFFER_ITEM_H_

#include <stdint.h>
//#include <boost/shared_ptr.hpp>
#include <memory>

#include "MediaBuffer.h"
#include "Errors.h"

namespace AwMirrorOp {

class BufferItem;
typedef std::shared_ptr<MediaBuffer> MediaBufferPtr;
typedef std::shared_ptr<BufferItem> BufferItemPtr;

class BufferItem final {

public:

    enum BufferState {
        // owned by BufferQueue. It transitions to DEQUEUED
        // when dequeueBuffer is called.
        FREE = 0,

        // owned by producer, It transitions to QUEUED
        // when queueBuffer is called.
        DEQUEUED = 1,

        // ownded by BufferQueue. It transitions to ACQUIRED
        // when acquireBuffer is called.
        QUEUED = 2,

        //owned by consumer. It transitions to FREE
        // when releaseBuffer is called.
        ACQUIRED = 3
    };

    BufferItem(MediaBufferPtr buffer);
    ~BufferItem();

    MediaBufferPtr buffer() const {
        return _mBuffer;
    };

    void setState(BufferState state) {
        _mState = state;
    };
    BufferState state() const {
        return _mState;
    };

    void setSlot(int32_t num) {
        _mSlot = num;
    };
    int32_t slot() const {
        return _mSlot;
    };

private:
    friend class BufferQueue;

    MediaBufferPtr _mBuffer;
    BufferState _mState;
    int32_t _mSlot;

    BufferItemPtr _mNextItem;

    void setNextBufferItem(BufferItemPtr item) {
        _mNextItem = item;
    };
    BufferItemPtr nextBufferItem() const {
        return _mNextItem;
    };
};

}; // namespace AwMirrorOp
#endif // _AW_BUFFER_ITEM_H_

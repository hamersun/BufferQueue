#ifndef _AW_BUFFER_QUEUE_H_
#define _AW_BUFFER_QUEUE_H_

#include <memory>
#include <mutex>

#include "BufferItem.h"
#include "Errors.h"

namespace AwMirrorOp {

//typedef boost::shared_ptr<BufferItem> BufferItemPtr;
typedef std::shared_ptr<BufferItem> BufferItemPtr;

class BufferQueue {

public:
    BufferQueue();
    virtual ~BufferQueue();

    status_t init(MediaType type, const uint16_t count, const uint32_t buffer_capacity);
    status_t initCheck() const;

    status_t dequeueBuffer(BufferItemPtr &buffer);
    status_t queueBuffer(BufferItemPtr &buffer);
    status_t acquireBuffer(BufferItemPtr &buffer);
    status_t releaseBuffer(BufferItemPtr &buffer);

private:
    BufferQueue(const BufferQueue &rhs);
    BufferQueue &operator=(const BufferQueue &rhs);

    status_t _preAllocateBufferPools(MediaType type, const uint16_t count, const uint32_t buffer_capacity);
    BufferItemPtr _createBufferItem(MediaType type, const uint32_t buffer_capacity);
    virtual void _addBuffer(BufferItemPtr &buffer);

    bool _mbInited;
    std::mutex _mMutex;

    uint64_t _mAccumulatedCount;

    BufferItemPtr _mFirstBuffer;
    BufferItemPtr _mLastBuffer;

    BufferItemPtr _mFirstFreeBuffer;
    BufferItemPtr _mLastFreeBuffer;
};

} // namespace AwMirrorOp

#endif // _AW_BUFFER_QUEUE_H_

#ifndef _AW_ORDERED_BUFFER_QUEUE_H_
#define _AW_ORDERED_BUFFER_QUEUE_H_

#include "BufferQueue.h"

namespace AwMirrorOp {

class OrderedBufferQueue : public BufferQueue {

public:
    float lostRate() const {
        return _lostRate;
    };

private:
    virtual status_t _addBuffer(BufferItemPtr buffer);
    float _lostRate;
}

}; // namespace AwMirrorOp
#endif // _AW_ORDERED_BUFFER_QUEUE_H_

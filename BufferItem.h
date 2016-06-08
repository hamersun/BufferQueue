#ifndef _AW_BUFFER_ITEM_H_
#define _AW_BUFFER_ITEM_H_

#include <stdint.h>
#include <boost/shared_ptr.hpp>
#include "Errors.h"

namespace AwMirrorOp {

class BufferItem {

public:

    enum BufferState {
	FREE = 0,
	DEQUEUED = 1,
	QUEUED = 2,
	ACQUIRED = 3
    };

    BufferItem(boost::shared_ptr<MediaBuffer> buffer, uint64_t serialNumber);
    ~BufferItem();

    status_t setState(BufferState state);
    BufferState getState();

    void setSlot(int32_t num);
    int32_t getSlot();

private:

    boost::shared_ptr<MediaBuffer> _mBuffer;
    BufferState _mState;
    int32_t _mSlot;
    uint64_t _mSN;
};

}; // namespace AwMirrorOp
#endif // _AW_BUFFER_ITEM_H_

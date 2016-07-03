#ifndef __AW_MEDIA_BUFFER_H_
#define __AW_MEDIA_BUFFER_H_

#include <stdint.h>
#include <memory>
#include "Errors.h"
#include "MediaTypes.h"

namespace AwMirrorOp {

class BufferItem;

class MediaBuffer {

public:
    MediaBuffer(const uint32_t capacity, const MediaType type);
    //MediaBuffer(void *data, const uint32_t capacity);
    virtual ~MediaBuffer();

    status_t copyData(void *data, const uint32_t size);
    status_t setDataSize(const uint32_t size);
    void* data() const;

    MediaType type() const;
    uint32_t capacity() const;
    uint32_t size() const;
    uint64_t serialnumber();
    status_t initCheck() const;

    std::shared_ptr<BufferItem> getBox();

private:
    friend class BufferItem;
    friend class BufferQueue;
    MediaBuffer(const MediaBuffer& rhs);
    MediaBuffer& operator=(const MediaBuffer& rhs);

    void setBox(std::shared_ptr<BufferItem> box);

    status_t _reallocate(const uint32_t capacity);
    void _setSerialNumber(uint64_t sn);

    void *_mData;
    status_t _mInitCheck;
    MediaType _mType;
    uint32_t _mCapacity; // capacity of the data buffer
    uint32_t _mSize;	// effective data size
    uint64_t _mSN;		// serial number of the data buffer which is incremental.

    std::weak_ptr<BufferItem> _mBox;
};

} // namespace AwMirrorOp

#endif // __AW_MEDIA_BUFFER_H_

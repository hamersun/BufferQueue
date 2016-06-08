#ifndef __AW_MEDIA_BUFFER_H_
#define __AW_MEDIA_BUFFER_H_

#include <stdint.h>
#include <boost/shared_ptr.hpp>
#include "Errors.h"

namespace AwMirrorOp {

class MediaBuffer {

public:
    MediaBuffer();
    MediaBuffer(int dataSize, char const*data);
    virtual ~MediaBuffer();

    void setData(char const* data, const uint32_t size);
    char* getData();

    uint32_t getSize();
    status_t reallocate(int dataSize);
    status_t initCheck();

private:
    MediaBuffer(const MediaBuffer& rhs);
    MediaBuffer& operator=(const MediaBuffer& rhs);
    const MediaBuffer& operator=(const MediaBuffer& rhs) const;

    boost::shared_ptr<char> _mData;
    uint32_t _mSize;
};

}; // namespace AwMirrorOp

#endif // __AW_MEDIA_BUFFER_H_

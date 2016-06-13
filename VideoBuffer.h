#ifndef __AW_VIDEO_BUFFER_H_
#define __AW_VIDEO_BUFFER_H_

#include "MediaTypes.h"
#include "MediaBuffer.h"
#include <memory>

namespace AwMirrorOp {

class VideoBuffer;
typedef std::shared_ptr<VideoBuffer> VideoBufferPtr;

class VideoBuffer : public MediaBuffer {

public:
    VideoBuffer(VideoFormat format);
    VideoBuffer(const uint32_t capacity, VideoFormat format);
    virtual ~VideoBuffer();

    static VideoBuffer* createBuffer(const uint32_t capacity, const VideoFormat format);

    void setIFrame(bool iframe);
    bool isIFrame() const;
    void setFormat(VideoFormat format);
    VideoFormat format() const;

private:
    bool _mbIFrame;
    VideoFormat _mFormat;
};

}; // namespace AwMirrorOp

#endif // __AW_VIDEO_BUFFER_H_

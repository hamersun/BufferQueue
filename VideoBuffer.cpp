#include "VideoBuffer.h"

namespace AwMirrorOp {

VideoBuffer* VideoBuffer::createBuffer(const uint32_t capacity, const VideoFormat format)
{
    VideoBuffer *buffer = new VideoBuffer(capacity, format);
    return buffer;
}

VideoBuffer::VideoBuffer(VideoFormat format) :
    MediaBuffer(0, VIDEO),
    _mFormat(H265),
    _mbIFrame(false)
{
}

VideoBuffer::VideoBuffer(const uint32_t capacity, VideoFormat format) :
    MediaBuffer(capacity, VIDEO),
    _mFormat(format),
    _mbIFrame(false)
{
}

VideoBuffer::~VideoBuffer()
{
}

void VideoBuffer::setIFrame(bool iframe)
{
    _mbIFrame = iframe;
}

bool VideoBuffer::isIFrame() const
{
    return _mbIFrame;
}

void VideoBuffer::setFormat(VideoFormat format)
{
    _mFormat = format;
}

VideoFormat VideoBuffer::format() const
{
    return _mFormat;
}

} // namespace AwMirrorOp

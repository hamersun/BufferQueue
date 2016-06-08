#ifndef __AW_VIDEO_BUFFER_H_
#define __AW_VIDEO_BUFFER_H_

#include "MediaTypes.h"

namespace AwMirrorOp {

class MediaBuffer;

class VideoBuffer : public MediaBuffer {

public:
    VideoBuffer(VideoType type);
    VideoBuffer(int dataSize, VideoType type);
    VideoBuffer(int dataSize, char const*data, VideoType type);
    ~VideoBuffer();

    void setIFrame(bool type);
    bool isIFrame();

private:
    bool _mbIFrame;
    VideoType _mType;
};

}; // namespace AwMirrorOp

#endif // __AW_VIDEO_BUFFER_H_

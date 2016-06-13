#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

#include "BufferQueue.h"
#include "VideoBuffer.h"

//#include "boost\thread.hpp"
//#include "boost\chrono.hpp"
//#include "boost\thread\scoped_thread.hpp"


using namespace std;
using namespace AwMirrorOp;

static bool bRunProducer = false;
static bool bRunConsumer = false;

void producer_thread(std::shared_ptr<BufferQueue> arg);
void consumer_thread(std::shared_ptr<BufferQueue> arg);

int main(int argc, char *argv[])
{
    //BufferQueue *bufQueue = new BufferQueue();
    std::shared_ptr<BufferQueue> bufQueue = std::make_shared<BufferQueue>();

    bufQueue->init(VIDEO, 8, 1024*20);

    //boost::thread t{producer_thread};
    std::thread t_p(producer_thread, bufQueue);
    std::thread t_c(consumer_thread, bufQueue);

    bufQueue.reset();
    t_p.join();
    t_c.join();
}


void producer_thread(std::shared_ptr<BufferQueue> arg)
{
    BufferItemPtr buf;
    //BufferQueue *queue = (BufferQueue*)(arg);
    std::shared_ptr<BufferQueue> queue = arg;
    if (queue == nullptr) {
        cerr << __FUNCTION__ << ": BufferQueue is null" << endl;
        return;
    }

    bRunProducer = true;
    status_t ret;
    while (bRunProducer) {

        if ((ret = queue->dequeueBuffer(buf)) != OK) {
            cerr << "dequeueBuffer failed..: " << ret << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }

        MediaBufferPtr dataBuf = buf->buffer();
        void *data = dataBuf->data();
        memset(data, 1, dataBuf->capacity());
        dataBuf->setDataSize(dataBuf->capacity());
        VideoBufferPtr video = std::dynamic_pointer_cast<VideoBuffer> (dataBuf);
        if (video != nullptr) {
            video->setIFrame(true);
        }
        queue->queueBuffer(buf);
    }
}

void consumer_thread(std::shared_ptr<BufferQueue> arg)
{
    BufferItemPtr buf;
    //BufferQueue *queue = (BufferQueue*)(arg);
    std::shared_ptr<BufferQueue> queue = arg;

    if (queue == nullptr) {
        cerr << __FUNCTION__ << ": BufferQueue is null" << endl;
        return;
    }

    bRunConsumer = true;
    status_t ret;
    while (bRunConsumer) {

        if ((ret = queue->acquireBuffer(buf)) != OK) {
            cerr << "acquireBuffer failed ...: " << ret << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }

        MediaBufferPtr dataBuf = buf->buffer();
        void *data = dataBuf->data();
        memset(data, 0, dataBuf->size());
        dataBuf->setDataSize(0);
        queue->releaseBuffer(buf);
    }
}

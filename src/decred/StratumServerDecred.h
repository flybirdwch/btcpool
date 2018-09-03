/*
 The MIT License (MIT)

 Copyright (c) [2018] [BTC.COM]

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#ifndef STRATUM_SERVER_DECRED_H_
#define STRATUM_SERVER_DECRED_H_

#include "StratumServer.h"

class ServerDecred;

class JobRepositoryDecred : public JobRepositoryBase<ServerDecred> {
public:
  JobRepositoryDecred(const char *kafkaBrokers, const char *consumerTopic, const string &fileLastNotifyTime, ServerDecred *server);

  StratumJob* createStratumJob() override;
  void broadcastStratumJob(StratumJob *sjob) override;

private:
  uint32_t lastHeight_;
};

class ServerDecred : public ServerBase<JobRepositoryDecred> {
public:
  explicit ServerDecred(int32_t shareAvgSeconds);
  StratumSession* createSession(evutil_socket_t fd, bufferevent *bev, sockaddr *saddr, const uint32_t sessionID) override;

protected:
  JobRepository* createJobRepository(const char *kafkaBrokers, const char *consumerTopic, const string &fileLastNotifyTime) override;
};

#endif

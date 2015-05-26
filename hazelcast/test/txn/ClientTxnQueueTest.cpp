//
// Created by sancar koyunlu on 9/18/13.
// Copyright (c) 2013 hazelcast. All rights reserved.


#include "ClientTxnQueueTest.h"
#include "HazelcastServerFactory.h"
#include "hazelcast/client/HazelcastClient.h"
#include "hazelcast/util/Thread.h"
#include "hazelcast/util/Util.h"

namespace hazelcast {
    namespace client {

        class HazelcastClient;

        namespace test {
            using namespace iTest;

            ClientTxnQueueTest::ClientTxnQueueTest(HazelcastServerFactory &serverFactory)
            : ClientTestSupport<ClientTxnQueueTest>("ClientTxnQueueTest")
            , instance(serverFactory)
            , client(getNewClient()) {
            }


            ClientTxnQueueTest::~ClientTxnQueueTest() {
            }

            void ClientTxnQueueTest::addTests() {
                addTest(&ClientTxnQueueTest::testTransactionalOfferPoll1, "testTransactionalOfferPoll1");
                addTest(&ClientTxnQueueTest::testTransactionalOfferPoll2, "testTransactionalOfferPoll2");
            }

            void ClientTxnQueueTest::beforeClass() {
            }

            void ClientTxnQueueTest::afterClass() {
                client.reset();
                instance.shutdown();
            }

            void ClientTxnQueueTest::beforeTest() {
            }

            void ClientTxnQueueTest::afterTest() {
            }

            void ClientTxnQueueTest::testTransactionalOfferPoll1() {
                std::string name = "defQueue";

                TransactionContext context = client->newTransactionContext();
                context.beginTransaction();
                TransactionalQueue<std::string> q = context.getQueue<std::string>(name);
                assertTrue(q.offer("ali"));
                assertEqual("ali", *(q.poll()));
                context.commitTransaction();
                assertEqual(0, client->getQueue<std::string>(name).size());
            }

            void testTransactionalOfferPoll2Thread(util::ThreadArgs& args) {
                util::CountDownLatch *latch = (util::CountDownLatch *)args.arg0;
                HazelcastClient *client = (HazelcastClient *)args.arg1;                
                latch->await();
                client->getQueue<std::string>("defQueue0").offer("item0");
            }

            void ClientTxnQueueTest::testTransactionalOfferPoll2() {

                util::CountDownLatch latch(1);
                util::Thread t(testTransactionalOfferPoll2Thread, &latch, client.get());
                TransactionContext context = client->newTransactionContext();
                context.beginTransaction();
                TransactionalQueue<std::string> q0 = context.getQueue<std::string>("defQueue0");
                TransactionalQueue<std::string> q1 = context.getQueue<std::string>("defQueue1");
                boost::shared_ptr<std::string> s;
                latch.countDown();
                s = q0.poll(10 * 1000);
                assertEqual("item0", *s);
                q1.offer(*s);

                try {
                    context.commitTransaction();
                } catch (exception::IException &e) {
                    assertTrue(false, e.what());
                }

                assertEqual(0, client->getQueue<std::string>("defQueue0").size());
                assertEqual("item0", *(client->getQueue<std::string>("defQueue1").poll()));
            }


        }
    }
}


#include "bit_queue.hpp"

int BitQueue::size() {
	return valid_bits;
}

class QueueDataLossException{};

void BitQueue::push(int val, int bsize) {
	if (valid_bits+bsize > 32) { //the queue is a 32 bit int so cannot store
	// more than 32 bits
		throw QueueDataLossException();
	}
	valid_bits += bsize;
	int mask = 0;
	for (int i = 0; i < bsize; i++) {
  		mask = mask<<1;
		mask++;
	}
	val = val&mask; //this gives us only the bsize lowest bits of val
	queue = queue<<bsize;
	queue = queue|val;
	
}

class QueueDataUnavailableException {};

int BitQueue::pop(int bsize) {
	if (bsize > valid_bits) {
		throw QueueDataUnavailableException();
	}

	valid_bits -= bsize;
	int mask = 0;
	for (int i = 0; i < bsize; i++) {
  		mask = mask<<1;
		mask++;
	}
	mask = mask&queue;
	queue = queue>>bsize;
	return mask;
}

void sendmsg(const char* msg) {

	BitQueue bitqueue;

	//for (char c : *msg) was originally doing this but doesn't work with
	//modifying the msg pointer during looping so switched to a while not
	// null loop
	while(*msg) {
		char c = *(msg++); //look I'm being snazzy with the post increment
		// like you showed last supo!
		if (c=='a') {
			bitqueue.push(0,1);
		} else if (c=='b') {
			bitqueue.push(2,2);
		} else if (c=='c') {
			bitqueue.push(12,4);
		} else if (c=='d') {
			bitqueue.push(13,4);
		}
	}
	bitqueue.push(7,3);
	while (bitqueue.size()>=8) {
		send(bitqueue.pop(8));
	}
	if (bitqueue.size() > 0) {
		bitqueue.push(0,8-bitqueue.size());
		send(bitqueue.pop(8));
	}
}

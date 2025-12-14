package main

import "sync"

type Brojac struct {
	counter int
	mutex sync.Mutex
	channel chan

	func Increment() {
		mutex.lock(counter);
		defer mutex.unlock();
		counter += 1;
	}

	func Decrement() {
		mutex.lock(counter);
		defer mutex.unlock();
		counter -= 1;
	}
}

func main() {
	var myBrojac: Brojac;
	var mojKanal := chan;
	mojKanal = make([int]chan);

	for i := 0; i < 4; i++ {
		go func() {
			
		}
	}
}
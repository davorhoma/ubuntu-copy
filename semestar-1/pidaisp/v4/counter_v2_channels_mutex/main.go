package main

import (
	"fmt"
	"sync"
)

type Counter struct {
	mutex sync.Mutex
	value int
}

func (counter *Counter) Increment() {
	counter.mutex.Lock()
	counter.value++
	counter.mutex.Unlock()
}

func main() {
	result := make(chan int)

	var counter Counter
	for range 4 {
		go uvecavaj(&counter, result)
	}

	fmt.Println("Result: ", <-result)
}

func uvecavaj(counter *Counter, result chan int) {
	for counter.value < 100 {
		counter.Increment()
	}

	result <- counter.value
}

package main

import (
	"fmt"
	"sync"
)

type Counter struct {
	mutex sync.Mutex
	value int
}

func (c *Counter) Increment() {
	c.mutex.Lock()
	c.value++
	c.mutex.Unlock()
}

func (c Counter) PrintValue() {
	fmt.Println("Value of counter is: ", c.value)
}

func main() {
	var counter Counter
	var wg sync.WaitGroup

	for range 4 {
		wg.Add(1)
		go uvecavaj(&counter, &wg)
	}

	wg.Wait()
	counter.PrintValue()
}

func uvecavaj(counter *Counter, wg *sync.WaitGroup) {
	defer wg.Done()
	for counter.value < 100 {
		counter.Increment()
	}
}

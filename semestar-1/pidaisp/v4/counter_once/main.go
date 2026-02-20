package main

import (
	"fmt"
	"sync"
)

type Counter struct {
	value int
}

func (counter *Counter) Increment() {
	counter.value++
}

func main() {
	var counter Counter = Counter{value: 5}
	var once sync.Once
	var wg sync.WaitGroup
	var count int

	increment := func() {
		count++
	}

	wg.Add(100)
	for i := range 100 {
		go func() {
			defer wg.Done()
			fmt.Println("i: ", i)
			once.Do(increment)
		}()
	}

	wg.Wait()
	fmt.Println("Counter: ", counter.value)
	fmt.Println("Count: ", count)

	a()
}

func a() {
	var count int
	increment := func() {
		count++
	}
	var once sync.Once
	var increments sync.WaitGroup
	increments.Add(100)
	for i := 0; i < 100; i++ {
		go func() {
			defer increments.Done()
			once.Do(increment)
		}()
	}
	increments.Wait()
	fmt.Printf("Count is %d\n", count)
}

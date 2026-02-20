package main

import (
	"fmt"
	"time"
)

func main() {
	var n int = 20
	// fmt.Print("Unesite N: ")
	// fmt.Scanf("%d", &n)

	elements := make(chan int)
	done := make(chan interface{})
	go fibonaci(n, elements)
	go write(elements, done)

	<-done
}

func fibonaci(n int, elements chan<- int) {
	if n < 2 {
		elements <- 1

		time.Sleep(1 * time.Second)
		close(elements)
		return
	}

	elements <- n
	fibonaci(n-1, elements)
}

func write(elements <-chan int, done chan interface{}) {
	for el := range elements {
		fmt.Printf("%d, ", el)
	}

	close(done)
}

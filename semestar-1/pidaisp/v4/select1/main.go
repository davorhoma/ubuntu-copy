package main

import "fmt"

func main() {
	var c1, c2 <-chan int
	var c3 chan<- int

	c1 = make(<-chan int)
	c2 = make(<-chan int)
	c3 = make(chan<- int)
	select {
	case <-c1:
		fmt.Println("Do something")
		// Do something
	case <-c2:
		fmt.Println("Do something")
		// Do something
	case c3 <- 2:
		// Do something
		fmt.Println("Do something")
	default:
		fmt.Println("DEFAULT")
	}

}

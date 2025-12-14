package main

import "fmt"

func main() {
	c := make(chan string)

	prvi := make(chan struct{})
	drugi := make(chan struct{})
	treci := make(chan struct{})
	end := make(chan struct{})

	go pisi(c, "cao", prvi, drugi, false)
	go pisi(c, "luka", drugi, treci, false)
	go pisi(c, "ivane", treci, prvi, true)

	prvi <- struct{}{}
	go citaj(c, end)

	<-end
}

func pisi(c chan<- string, word string, wait, next chan struct{}, closeChannel bool) {
	for i := 0; i < 10; i++ {
		<-wait
		c <- word
		next <- struct{}{}
	}

	if closeChannel {
		close(c)
	}
}

func citaj(c <-chan string, end chan<- struct{}) {
	var word string
	for i := 0; i < 30; i++ {
		word = <-c
		if i%3 == 0 {
			fmt.Print("\n", i, " ")
		}
		fmt.Print(word, " ")
	}

	// for word := range c {
	// 	fmt.Println(word)
	// }
	close(end)
}

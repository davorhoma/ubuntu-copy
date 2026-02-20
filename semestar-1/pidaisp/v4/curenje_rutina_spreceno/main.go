package main

import (
	"fmt"
	"time"
)

func main() {
	doWork := func(done <-chan interface{}, strings <-chan string) <-chan interface{} {
		terminated := make(chan interface{})
		go func() {
			defer fmt.Println("doWork exited.")
			defer close(terminated)
			for {
				select {
				case s := <-strings:
					fmt.Println(s)
				case <-done: // Korišćenje for-select šablona kako bi se prekinuo rad rutine
					return
				}
			}
		}()
		return terminated
	}
	done := make(chan interface{})
	terminated := doWork(done, nil)
	go func() { // Pokretanje rutine koja će zaustaviti doWork rutinu
		fmt.Println("Sleeping for 1 second...")
		time.Sleep(1 * time.Second)
		fmt.Println("Canceling doWork goroutine...")
		close(done)
	}()
	<-terminated // Spajanje (engl. join) main rutine I njege dete rutine woWork
	fmt.Println("Done.")

}

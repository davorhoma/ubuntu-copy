package main

import (
	"fmt"
	"math"
)

func main() {
	n := unesiteN()
	niz := unesiteNiz(n)

	results := make(chan int)
	// defer close(results)

	var brojKanala int
	fmt.Print("Unesite broj kanala: ")
	fmt.Scanf("%d", &brojKanala)
	nizZaprobu := make([]int, brojKanala)
	kanali := make([]chan struct{}, brojKanala)
	length := len(nizZaprobu) / brojKanala
	var part []int
	for i := 0; i < brojKanala; i++ {
		part = niz[i*length : i+1*length]
		go findMinProba(results, part, kanali[i], kanali[i+1])
	}

	fourth := len(niz) / 4
	niz1 := niz[:fourth]
	niz2 := niz[fourth : 2*fourth]
	niz3 := niz[2*fourth : 3*fourth]
	niz4 := niz[3*fourth:]

	ch1 := make(chan struct{})
	ch2 := make(chan struct{})
	ch3 := make(chan struct{})
	done := make(chan struct{})

	go findMin(results, &niz4, nil, ch1)
	go findMin(results, &niz3, ch1, ch2)
	go findMin(results, &niz2, ch2, ch3)
	go findMin(results, &niz1, ch3, nil)

	go write(results, done)

	<-done
	fmt.Println("ENDE")
}

func unesiteN() int {
	var n int
	for {
		fmt.Print("Unesite n (> 4): ")
		_, err := fmt.Scanf("%d", &n)
		if err != nil {
			continue
		}

		if n > 4 {
			break
		}
	}

	return n
}

func unesiteNiz(n int) []int {
	niz := make([]int, n)
	fmt.Printf("Unesite %d brojeva:\n", n)
	for i := range n {
		fmt.Scanf("%d", &niz[i])
	}

	return niz
}

func findMin(results chan int, array *[]int, wait, signal chan struct{}) {
	min := math.MaxInt
	for _, val := range *array {
		if val < min {
			min = val
		}
	}

	if wait != nil {
		<-wait
	}

	results <- min

	if signal != nil {
		close(signal)
	}
}

func findMinProba(results chan int, array []int, wait, signal chan struct{}) {
	min := math.MaxInt
	for _, val := range array {
		if val < min {
			min = val
		}
	}

	if wait != nil {
		<-wait
	}

	results <- min

	if signal != nil {
		close(signal)
	}
}

func write(results chan int, done chan struct{}) {
	for counter := 0; counter < 4; counter++ {
		fmt.Printf("Min %d: %d\n", counter, <-results)
	}

	close(done)
}

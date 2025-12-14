package main

import (
	"fmt"
	"math"
)

func main() {
	n := unesiteN()
	niz := unesiteNiz(n)

	fmt.Println("\nNIZ")
	for _, i := range niz {
		fmt.Printf("%d,", i)
	}
	results := make(chan int)

	var brojKanala int
	fmt.Print("Unesite broj kanala: ")
	fmt.Scanf("%d", &brojKanala)
	fmt.Println("Broj kanala: ", brojKanala)

	var kanali []chan struct{}
	for i := 0; i < brojKanala; i++ {
		kanali = append(kanali, make(chan struct{}))
	}

	length := len(niz) / brojKanala
	var part []int
	for i := 0; i < brojKanala; i++ {
		if i == 0 {
			part = niz[:length]
			go findMinProba(results, part, kanali[i+1], nil)
		} else if i == brojKanala-1 {
			part = niz[i*length:]
			go findMinProba(results, part, nil, kanali[i])
		} else {
			part = niz[i*length : (i+1)*length]
			go findMinProba(results, part, kanali[i+1], kanali[i])
		}

		ispisiNiz(part)
	}

	done := make(chan struct{})

	go write(results, done, brojKanala)

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

func ispisiNiz(niz []int) {
	fmt.Println("\nNIZ")
	for _, i := range niz {
		fmt.Printf("%d,", i)
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

func write(results chan int, done chan struct{}, brojKanala int) {
	for counter := 5; counter > 0; counter-- {
		fmt.Printf("Min %d: %d\n", counter, <-results)
	}

	close(done)
}

package main

import (
	"fmt"
	"sync"
)

func main() {
	var n int
	var brojevi []int
	fmt.Print("Unesite N: ")
	fmt.Scanf("%d", &n)

	fmt.Print("Unesite ", n, " brojeva: ")
	for i := 0; i < n; i++ {
		var broj int
		fmt.Scanf("%d", &broj)
		brojevi = append(brojevi, broj)
	}

	var wg sync.WaitGroup
	wg.Add(5)
	c := make(chan int, 5)
	go findMin(brojevi[0:n/5], c, &wg)
	go findMin(brojevi[n/5:2*n/5], c, &wg)
	go findMin(brojevi[2*n/5:3*n/5], c, &wg)
	go findMin(brojevi[3*n/5:4*n/5], c, &wg)
	go findMin(brojevi[4*n/5:], c, &wg)

	minimumi := make([]int, 5)
	minimumi[0], minimumi[1], minimumi[2], minimumi[3], minimumi[4] = <-c, <-c, <-c, <-c, <-c
	// for i := 0; i < 5; i++ {
	// 	minimumi[i] = <-c
	// }

	wg.Wait()
	wg.Add(1)
	findMin(minimumi, c, &wg)
	fmt.Println("Minimum je: ", <-c)
}

func findMin(brojevi []int, c chan int, wg *sync.WaitGroup) {
	min := brojevi[0]
	for _, broj := range brojevi {
		if broj < min {
			min = broj
		}
	}

	c <- min
	wg.Done()
}

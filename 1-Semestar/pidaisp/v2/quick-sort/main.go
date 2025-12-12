package main

import (
	"fmt"
	"math/rand"
	"sort"
	"sync"
	"time"
)

func main() {
	rand.Seed(42)

	n := 1_000_000
	// n := 30
	niz := make([]int, n)
	max, min := 10_000, 1
	for i := range niz {
		niz[i] = rand.Intn(max-min+1) + min
	}

	nizCopy := make([]int, n)
	copy(nizCopy, niz)

	izmeriSort(nizCopy, quickSort, "QuickSort trajanje")
	izmeriSort(nizCopy, quickSortParallel, "QuickSortParallel trajanje")
	izmeriSort(nizCopy, quickSortWaitGroup, "QuickSortWaitGroup trajanje")

	start := time.Now()
	niz2 := quickSort(niz)
	duration := time.Since(start)
	fmt.Printf("QuickSort trajanje: %v\n", duration)

	start2 := time.Now()
	sort.Ints(nizCopy)
	duration2 := time.Since(start2)
	fmt.Printf("sort.Ints trajanje: %v\n", duration2)

	for i := 0; i < n; i++ {
		if niz2[i] != nizCopy[i] {
			fmt.Println("Nizovi se razlikuju!")
			break
		}
	}
}

func izmeriSort(niz []int, sortingFuction func([]int) []int, ispis string) {
	start := time.Now()
	sortingFuction(niz)
	duration := time.Since(start)
	fmt.Printf("%s: %v\n", ispis, duration)
}

func quickSort(niz []int) []int {
	var first []int
	var second []int

	if len(niz) <= 1 {
		return niz
	}

	// pivot := niz[0]
	pivot := medianOfThree(niz[0], niz[len(niz)/2], niz[len(niz)-1])
	pivots := make([]int, 0)
	for _, i := range niz {
		if i < pivot {
			first = append(first, i)
		} else if i > pivot {
			second = append(second, i)
		} else {
			pivots = append(pivots, i)
		}
	}

	sortedFirst := quickSort(first)
	sortedSecond := quickSort(second)

	result := make([]int, 0, len(sortedFirst)+len(pivots)+len(sortedSecond))
	result = append(result, sortedFirst...)
	result = append(result, pivots...)
	return append(result, sortedSecond...)
}

func quickSortParallel(niz []int) []int {
	var first []int
	var second []int

	if len(niz) <= 1 {
		return niz
	}

	pivot := medianOfThree(niz[0], niz[len(niz)/2], niz[len(niz)-1])
	pivots := make([]int, 0)
	for _, i := range niz {
		if i < pivot {
			first = append(first, i)
		} else if i > pivot {
			second = append(second, i)
		} else {
			pivots = append(pivots, i)
		}
	}

	var sortedFirst, sortedSecond []int
	done := make(chan bool)

	go func() {
		sortedFirst = quickSort(first)
		done <- true
	}()

	go func() {
		sortedSecond = quickSort(second)
		done <- true
	}()

	<-done
	<-done

	result := make([]int, 0, len(sortedFirst)+len(pivots)+len(sortedSecond))
	result = append(result, sortedFirst...)
	result = append(result, pivots...)
	return append(result, sortedSecond...)
}

func quickSortWaitGroup(niz []int) []int {
	var first []int
	var second []int

	if len(niz) <= 1 {
		return niz
	}

	pivot := medianOfThree(niz[0], niz[len(niz)/2], niz[len(niz)-1])
	pivots := make([]int, 0)
	for _, i := range niz {
		if i < pivot {
			first = append(first, i)
		} else if i > pivot {
			second = append(second, i)
		} else {
			pivots = append(pivots, i)
		}
	}

	var sortedFirst, sortedSecond []int
	var wg sync.WaitGroup
	wg.Add(2)

	go func() {
		defer wg.Done()
		sortedFirst = quickSort(first)
	}()

	go func() {
		defer wg.Done()
		sortedSecond = quickSort(second)
	}()

	wg.Wait()

	result := make([]int, 0, len(sortedFirst)+len(pivots)+len(sortedSecond))
	result = append(result, sortedFirst...)
	result = append(result, pivots...)
	return append(result, sortedSecond...)
}

func medianOfThree(a, b, c int) int {
	if (a <= b && b <= c) || (c <= b && b <= a) {
		return b
	} else if (b <= a && a <= c) || (c <= a && a <= b) {
		return a
	} else {
		return c
	}
}

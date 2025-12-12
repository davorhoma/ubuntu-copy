package main

import "fmt"

func main() {
	fmt.Println("Unesite N: ")
	var n int
	_, err := fmt.Scanf("%d", &n)
	if err != nil {
		fmt.Println("Error: ", err)
		return
	}

	niz := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Printf("Unesite niz[%d]: ", i)
		fmt.Scanf("%d", &niz[i])
	}

	fmt.Println("Nesortiran niz: ", niz)
	sort(&niz)
	fmt.Println("Sortiran niz: ", niz)
}

func sort(niz *[]int) []int {
	for i, _ := range *niz {
		for j, _ := range *niz {
			if (*niz)[i] < (*niz)[j] {
				temp := (*niz)[j]
				(*niz)[j] = (*niz)[i]
				(*niz)[i] = temp
			}
		}
	}

	return *niz
}

package main

import "fmt"

type Stack interface {
	push(value int)
	pop() int
	top() int
	isEmpty() bool
}

type SpregnutStack struct {
	value int
	head *SpregnutStack
	next *SpregnutStack
}

func (ss *SpregnutStack) push(value int) {
	if (ss.head == nil) {
		ss.value = value
	} else {
		var tempNext *SpregnutStack = ss.next
		for (tempNext != nil) {
			tempNext = ss.next
		}

		tempNext.value = value
	}
}

func (ss *SpregnutStack) pop() int {
	if (ss.value == nil) { // mora se koristiti pokazivac na int
		return -1
	}

	var tempNext *SpregnutStack = ss.next
	for(tempNext != nil) {
		tempNext = tempNext.next
	}

	retVal := tempNext.value
	tempNext = nil
	return retVal
}

func main() {
	var ss SpregnutStack
	ss.push(5)
	fmt.Printf("ss.pop(): %d", ss.pop())

}
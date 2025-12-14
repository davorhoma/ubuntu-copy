package main

import (
	"fmt"
	"strconv"
)

type Stack interface {
	pop() int
	push()
	top() int
	isEmpty() bool

	toString() string
}

type MyStack struct {
	s []int
}

func (myStack *MyStack) pop() int {
	value := myStack.s[len(myStack.s)-1]
	myStack.s = myStack.s[:len(myStack.s)-1]
	return value
} 

func (myStack *MyStack) push(value int) {
	myStack.s = append(myStack.s, value)
}

func (myStack *MyStack) top() int {
	value := myStack.s[0]
	return value
}

func (myStack *MyStack) isEmpty() bool {
	return len(myStack.s) == 0
}

func (myStack *MyStack) toString() string {
	var retVal string
	for _, number := range myStack.s {
		retVal += strconv.Itoa(number) + ", "
	}

	return retVal
}

func main() {
	var myStack MyStack
	myStack.push(5)
	myStack.push(20)
	myStack.push(30)
	myStack.push(14)

	fmt.Printf("myStack.pop(): %d\n", myStack.pop())
	fmt.Printf("myStack.pop(): %d\n", myStack.pop())
	fmt.Printf("myStack.top(): %d\n", myStack.top())
	fmt.Printf("myStack.isEmpty(): %t\n", myStack.isEmpty())

	for _, value := range myStack.s {
		fmt.Printf("E: %d\n", value)
	}

	fmt.Println("myStack: ", myStack.s)
	fmt.Printf("myStack: " + myStack.toString())
}
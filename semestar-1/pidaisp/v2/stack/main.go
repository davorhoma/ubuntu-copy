package main

import "fmt"

type Stack struct {
	array []int
}

func (s *Stack) push(value int) {
	s.array = append(s.array, value)
}

func (s *Stack) pop() (int, error) {
	if len(s.array) > 0 {
		value := s.array[len(s.array)-1]
		s.array = s.array[:len(s.array)-1]
		return value, nil
	} else {
		return -1, nil
	}
}

func (s *Stack) top() (int, error) {
	if len(s.array) > 0 {
		return s.array[0], nil
	} else {
		return -1, nil
	}
}

func (s *Stack) isEmpty() bool {
	return len(s.array) > 0
}

func main() {
	var myStack Stack
	myStack.push(5)
	myStack.push(15)
	myStack.push(4)
	myStack.push(6)

	val, err := myStack.pop()
	if err == nil {
		fmt.Println("myStack.pop(): ", val)
	}

	val, err = myStack.pop()
	if err == nil {
		fmt.Println("myStack.pop(): ", val)
	}

	val, err = myStack.pop()
	if err == nil {
		fmt.Println("myStack.pop(): ", val)
	}

	val, err = myStack.pop()
	if err == nil {
		fmt.Println("myStack.pop(): ", val)
	}

	val, err = myStack.top()
	if err == nil {
		fmt.Println("myStack.top(): ", val)
	}

	fmt.Println("myStack.isEmpty():", myStack.isEmpty())
}

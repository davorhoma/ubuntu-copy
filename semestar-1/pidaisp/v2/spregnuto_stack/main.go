package main

import (
	"errors"
	"fmt"
)

type SpregnutStack struct {
	head  *SpregnutStack
	next  *SpregnutStack
	value int
}

func (s *SpregnutStack) push(value int) {
	if s.head == nil {
		s.value = value
		s.head = s
		return
	}

	tempNext := s.next
	prev := s
	for {
		if tempNext != nil {
			prev = tempNext
			tempNext = tempNext.next
		} else {
			// tempNext = &SpregnutStack{
			// 	value: value,
			// }
			prev.next = &SpregnutStack{
				head:  s.head,
				value: value,
				next:  nil,
			}

			break
		}
	}
}

func (s *SpregnutStack) pop() (int, error) {
	if s.head == nil {
		return -1, errors.New("stack is empty")
	}

	tempNext := s
	prev := s
	for {
		if tempNext.next != nil {
			prev = tempNext
			tempNext = tempNext.next
		} else {
			if tempNext == s.head {
				s.head = nil
			}
			value := tempNext.value
			prev.next = nil
			return value, nil
		}
	}
}

func (s *SpregnutStack) top() (int, error) {
	if s.head == nil {
		return -1, errors.New("stack is empty")
	}

	return s.value, nil
}

func (s *SpregnutStack) isEmpty() bool {
	return s.head == nil
}

func main() {
	var myStack SpregnutStack
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

	fmt.Println("myStack.isEmpty():", myStack.isEmpty())

	val, err = myStack.top()
	if err == nil {
		fmt.Println("myStack.top(): ", val)
	}

	val, err = myStack.pop()
	if err == nil {
		fmt.Println("myStack.pop(): ", val)
	}

	fmt.Println("myStack.isEmpty():", myStack.isEmpty())
}

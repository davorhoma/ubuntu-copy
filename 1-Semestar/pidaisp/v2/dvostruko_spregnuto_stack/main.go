package main

import (
	"errors"
	"fmt"
)

type DvostrukoSpregnutStack struct {
	head  *DvostrukoSpregnutStack
	next  *DvostrukoSpregnutStack
	prev  *DvostrukoSpregnutStack
	value int
}

func (s *DvostrukoSpregnutStack) push(value int) {
	if s.head == nil {
		s.head = s
		s.value = value
		return
	}

	tempNext := s.next
	prev := s
	for {
		if tempNext != nil {
			prev = tempNext
			tempNext = tempNext.next
		} else {
			prev.next = &DvostrukoSpregnutStack{
				head:  s.head,
				prev:  prev,
				next:  nil,
				value: value,
			}

			return
		}
	}
}

func (s *DvostrukoSpregnutStack) pop() (int, error) {
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
			tempNext = nil
			prev.next = nil

			return value, nil
		}
	}
}

func (s *DvostrukoSpregnutStack) top() (int, error) {
	if s.head == nil {
		return -1, errors.New("stack is empty")
	}

	return s.value, nil
}

func (s *DvostrukoSpregnutStack) isEmpty() bool {
	return s.head == nil
}

func main() {
	var myStack DvostrukoSpregnutStack
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

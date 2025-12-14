package main

import "errors"

func createPalindrome(s string) (string,error) {
	if len(s)%2 == 0 {
		return "",errors.New("String mora imati neparan broj karaktera")
	}
	slen := len(s)
	for i:= slen-2; i >=0; i--{
		s = s + string(s[i])
	}
	return s,nil
}

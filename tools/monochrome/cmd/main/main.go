package main

import (
	"flag"
	"fmt"
	"image"

	_ "golang.org/x/image/bmp"

	_ "image/jpeg"
	_ "image/png"

	"os"

	"github.com/polldo/dolp/tools/monochrome"
)

func main() {
	var filepath string
	flag.StringVar(&filepath, "i", "", "path of image to convert")
	flag.Parse()
	if filepath == "" {
		fmt.Println("please provide a filepath")
		os.Exit(1)
	}

	img, err := openImage(filepath)
	if err != nil {
		fmt.Printf("cannot open file %s: %s\n", filepath, err)
		os.Exit(1)
	}

	b := monochrome.Convert(img)
	fmt.Printf("Image for c++: \n%s\n", b.ToCpp())
	fmt.Println()
	fmt.Printf("Image for python: \n%s\n", b.ToPy())
}

func openImage(filepath string) (image.Image, error) {
	f, err := os.Open(filepath)
	if err != nil {
		return nil, fmt.Errorf("opening file %s: %w", filepath, err)
	}
	defer f.Close()
	img, _, err := image.Decode(f)
	return img, err
}

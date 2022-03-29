package monochrome

import (
	"fmt"
	"image"
	"image/color"
	"strings"
)

type Monochrome struct {
	val    []byte
	width  int
	height int
}

func (m *Monochrome) ToCpp() string {
	s := "const uint8_t image[] = { "
	s += fmt.Sprintf("0x%02x, 0x%02x, ", m.width, m.height)
	for _, b := range m.val {
		s += fmt.Sprintf("0x%02x, ", b)
	}
	s = strings.TrimRight(s, ", ")
	s += " };"
	return s
}

func (m *Monochrome) ToPy() string {
	s := "image = bytearray(b'"
	s += fmt.Sprintf("\\x%02x\\x%02x", m.width, m.height)
	for _, b := range m.val {
		s += fmt.Sprintf("\\x%02x", b)
	}
	s += "')"
	return s
}

func Convert(img image.Image) *Monochrome {
	w, h := img.Bounds().Dx(), img.Bounds().Dy()
	conv := make([]byte, 0, w*h/8)

	for y := 0; y < h; y += 8 {
		for x := 0; x < w; x++ {
			var col byte
			for j := 7; j >= 0; j-- {
				pixel := 1
				if color.Gray16Model.Convert(img.At(x, y+j)) == color.Black {
					pixel = 0
				}
				col = (col << 1) | byte(pixel)
			}
			conv = append(conv, col)
		}
	}

	return &Monochrome{val: conv, width: w, height: h}
}

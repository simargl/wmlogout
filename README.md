# wmlogout

desktop session logout dialog made in c++ and fltk with colors matching adwaita dark theme

buttons with hover effect

![Screenshot](https://raw.githubusercontent.com/simargl/wmlogout/main/screenshots/wmlogout.png)

## Installation

Install wmlogout with:

```bash
  apt install libfltk1.3-dev -y
  g++ `fltk-config --cxxflags` wmlogout.cxx `fltk-config --ldflags` -o wmlogout; ./wmlogout
```

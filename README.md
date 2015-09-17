# Dancing-Links
C implementation of Knuth's dancing links algorithm acording to his article: [Dancing Links](https://www.ocf.berkeley.edu/~jchu/publicportal/sudoku/0011047.pdf).
The purpose to Knuth's algorithm is to solve the Exact Set Cover.

Many problems can be solved as an exact set cover, such as polyminos, sudoku and n-queens problem.

See the wikipedia [page](https://en.wikipedia.org/wiki/Exact_cover) for more details.

# Usage

`maker.jl` is a [Julia](http://julialang.org/) code that writes the polymino as an exact set cover problem.
One can also pipe some other exact set cover instance to the binary.
The binary can be built using ```make```.

One possible usage is:
```
./dlx < 5x8_2xAll_freePieces.dat
```

or

```
julia maker.jl | ./dlx
```



Each solution found (if any) will be in a separate block.

# License

See `LICENSE` for details.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 51 Franklin
Street, Fifth Floor, Boston, MA 02110-1301  USA


/*
 * Copyright (C) 2021  h3nnn4n, aka Renan S. Silva
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef SRC_FILE_UTILS_H_
#define SRC_FILE_UTILS_H_

/* Size of each input chunk to be read and allocate for. */
#ifndef READALL_CHUNK
#define READALL_CHUNK 262144
#endif

#define READALL_OK      0  /* Success */
#define READALL_INVALID -1 /* Invalid parameters */
#define READALL_ERROR   -2 /* Stream error */
#define READALL_TOOMUCH -3 /* Too much input */
#define READALL_NOMEM   -4 /* Out of memory */

void ensure_directory_exists(char *directory);
int  file_exists(char *filepath);
int  mkdir_p(const char *path);
int  readall(FILE *in, char **dataptr, size_t *sizeptr);

#endif /* SRC_FILE_UTILS_H_ */

/**
 *
 *  Copyright 2016 Netflix, Inc.
 *
 *     Licensed under the GNU Lesser General Public License, Version 3
 *     (the "License"); you may not use this file except in compliance
 *     with the License. You may obtain a copy of the License at
 *
 *         http://www.gnu.org/licenses/lgpl-3.0.en.html
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 *     implied. See the License for the specific language governing
 *     permissions and limitations under the License.
 *
 */

#include <stdio.h>
#include <stdlib.h>

int read_image(FILE *rfile, void *buf, int width, int height, int stride, int elem_size)
{
	char *byte_ptr = buf;
	int i;
	int ret = 1;

	if (width <= 0 || height <= 0 || elem_size <= 0)
	{
		goto fail_or_end;
	}

	for (i = 0; i < height; ++i)
	{
		if (fread(byte_ptr, elem_size, width, rfile) != (size_t)width)
		{
			goto fail_or_end;
		}

		byte_ptr += stride;
	}

	ret = 0;

fail_or_end:
	return ret;
}

int write_image(FILE *wfile, const void *buf, int width, int height, int stride, int elem_size)
{
	const char *byte_ptr = buf;
	int i;
	int ret = 1;

	if (width <= 0 || height <= 0 || elem_size <= 0)
	{
		goto fail_or_end;
	}

	for (i = 0; i < height; ++i)
	{
		if (fwrite(byte_ptr, elem_size, width, wfile) != (size_t)width)
		{
			goto fail_or_end;
		}

		byte_ptr += stride;
	}

	ret = 0;

fail_or_end:
	return ret;
}

int read_image_b2s(FILE * rfile, float *buf, float off, int width, int height, int stride)
{
	char *byte_ptr = (char *)buf;
	unsigned char *tmp_buf = 0;
	int i, j;
	int ret = 1;

	if (width <= 0 || height <= 0)
	{
		goto fail_or_end;
	}

	if (!(tmp_buf = malloc(width)))
	{
		goto fail_or_end;
	}

	for (i = 0; i < height; ++i)
	{
		float *row_ptr = (float *)byte_ptr;

		if (fread(tmp_buf, 1, width, rfile) != (size_t)width)
		{
			goto fail_or_end;
		}

		for (j = 0; j < width; ++j)
		{
			row_ptr[j] = tmp_buf[j] + off;
		}

		byte_ptr += stride;
	}

	ret = 0;

fail_or_end:
	free(tmp_buf);
	return ret;
}

int read_image_b2d(FILE *rfile, double *buf, double off, int width, int height, int stride)
{
	char *byte_ptr = (char *)buf;
	unsigned char *tmp_buf = 0;
	int i, j;
	int ret = 1;

	if (width <= 0 || height <= 0)
	{
		goto fail_or_end;
	}

	if (!(tmp_buf = malloc(width)))
	{
		goto fail_or_end;
	}

	for (i = 0; i < height; ++i)
	{
		double *row_ptr = (double *)byte_ptr;

		if (fread(tmp_buf, 1, width, rfile) != (size_t)width)
		{
			goto fail_or_end;
		}

		for (j = 0; j < width; ++j)
		{
			row_ptr[j] = tmp_buf[j] + off;
		}

		byte_ptr += stride;
	}

	ret = 0;

fail_or_end:
	free(tmp_buf);
	return ret;
}
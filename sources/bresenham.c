/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomes-t <ngomes-t@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 01:00:58 by ngomes-t          #+#    #+#             */
/*   Updated: 2022/12/18 01:01:11 by ngomes-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// função para desenhar uma linha usando o algoritmo de Bresenham
void drawLine(int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int p = 2 * dy - dx;
    int twoDy = 2 * dy;
    int twoDyMinusDx = 2 * (dy - dx);
    int x, y;

    // determinar qual ponto é o inicial e qual é o final
    if (x0 > x1)
    {
        x = x1;
        y = y1;
        x1 = x0;
    }
    else
    {
        x = x0;
        y = y0;
    }

    // colocar o primeiro ponto
    putpixel(x, y);

    while (x < x1)
    {
        x++;
        if (p < 0)
        {
            p += twoDy;
        }
        else
        {
            y++;
            p += twoDyMinusDx;
        }

        // colocar o próximo ponto
        putpixel(x, y);
    }
}

int main()
{
    int x0 = 2, y0 = 3, x1 = 9, y1 = 8;

    // chamar a função para desenhar a linha
    drawLine(x0, y0, x1, y1);

    return 0;
}

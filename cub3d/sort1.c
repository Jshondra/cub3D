
void	bubble_sort(double *num, double *s, int size)
{
	int i;
	int j;
	int temp;
	int t;

	i = -1;
	j = (size - 1);
	while (++i < size - 1)
	{
		while (j > i)
		{
			if (num[j] > num[j - 1])
			{
				temp = num[j - 1];
				num[j - 1] = num[j];
				num[j] = temp;
				t = s[j - 1];
				s[j - 1] = s[j];
				s[j] = t;
			}
			j--;
		}
		j = (size - 1);
	}
}

int isInSubway(char *subway)
{
	// subway가 지하철역에 해당하나?
	Dijkstra *search = Dlist;
	while (search != NULL)
	{
		if (strcmp(search->name, subway) == 0)
		{
			return 1;
		}
		search = search->next;
	}
	return -999;
}

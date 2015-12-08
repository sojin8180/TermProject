void printRDLL(void)
{
	ForPrint *temp = head;
	int cnt = 0;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	if (strcmp(temp->name, temp->prev->name) == 0)
	{
		startrans = 1;
	}
	while (temp->prev != NULL)
	{
		if (cnt % 7 == 0)
		{
			printf("\n");
		}
		if (strcmp(temp->name, temp->prev->name) != 0)
		{
			printf("%s->", temp->name);
		}
		temp = temp->prev;
		cnt++;
	}
	printf("%s", temp->name);

}

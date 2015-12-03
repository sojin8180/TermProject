void connectTransfer(void) // 환승역을 연결
{
	// 환승역 끼리 연결해야 한다는 사실
	// 중복된 이름을 찾아 그 둘을 연결.
	mysubway *chain = map;
	mysubway *chain2 = map;
	while (chain->next != NULL)
	{
		chain2 = chain->next;
		while (chain2 != NULL)
		{
			if (strcmp(chain->name, chain2->name) == 0)
			{
				if (strcmp(chain->kind, chain2->kind) != 0)
				{
					addTrans(chain, chain2, 1);
					//			printf("%s %s %s %s\n", chain->name, chain->kind, chain2->name, chain2->kind);
				}
			}
			chain2 = chain2->next;
		}
		chain = chain->next;
	}

}

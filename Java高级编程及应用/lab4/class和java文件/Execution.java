
class Execution implements Execute{
		int[] data; //存放现有犯人的序号
		int currNumber; //存放现有犯人的总数
		int currPos; //存放下一次要被处死的犯人在数组中的位置
		long currStep; //存放下一次寻找犯人的步长
		public void initData(int totalNumber, int initPos, long initStep){
			currNumber = totalNumber;
			currPos = initPos;
			currStep = initStep;
			data = new int[totalNumber];
			for (int i=0; i<totalNumber; i++)
				data[i] = i;
		}
		public int getSurvival(){
			return data[0];
		}
		public void execute(){
			//请添加自己的代码
			while (currNumber>1){//当前人数大于1人, 才能继续处决
		         int originStep=data[currPos];//初始犯人号是第一轮的原始步长的一部分
		         currStep+=originStep;//第一轮要把步长加上初始犯人号
		            for(int i=currPos;i<currNumber-1;++i){//遍历
		                data[i]=data[i+1];//每次更新犯人数组
		            }
		            currNumber--;
		            currPos= (int) ((currPos+currStep-1)%currNumber);
		    }
		}
		//请添加所需成员变量和成员方法：
}



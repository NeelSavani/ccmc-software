#include "Kameleon.h"
#include "FileReader.h"
#include "OpenGGCM.h"
#include "BATSRUS.h"
#include "ENLIL.h"
#include "MAS.h"
#include <string>

namespace ccmc
{
	long Kameleon::open(const std::string& filename)
	{
		//need to store filename
		//need to intialize relevant information


		FileReader fileReader;
		fileReader.open(filename);
		this->modelName = (fileReader.getGlobalAttribute("model_name")).getAttributeString();
		fileReader.close();
		std::cout << "modelName: " << modelName << std::endl;
		if (modelName == "open_ggcm" || modelName == "ucla_ggcm")
		{
			std::cout << "created OpenGGCM object" << std::endl;
			model = new OpenGGCM();
		} else if (modelName == "batsrus")
		{
			std::cout << "created BATSRUS object" << std::endl;
			model = new BATSRUS();
		} else if (modelName == "enlil")
		{
			std::cout << "created ENLIL object" << std::endl;
			model = new ENLIL();
		} else if (modelName == "mas")
		{
			std::cout << "created MAS object" << std::endl;
			model = new MAS();
		}

		long status = -1;
		if (model != NULL)
		{
			status = model->open(filename);


			//current_cdf_id = get_current_CDFid();
			initializeExtraInformation();

		}
		return status;

	}
}

// Matthew Applin
// resourceType class

class resourceType
{
public:
	double price;
	std::vector<resourceType> MaterialRequirement;
	std::vector<int> minMaterial;
	std::vector<int> maxMaterial;
	int minManufacturingLevel;
	int maxManufacturingLevel;
	int minAgricultureLevel;
	int maxAgricultureLevel;
	int minMiningLevel;
	int maxMiningLevel;
	double massPerUnit;
	double sizePerUnit;
	double standardProductionRate;
	double maxProductionRate;
	double minProductionRate;
	resourceType* resourceMultiplyer;
};
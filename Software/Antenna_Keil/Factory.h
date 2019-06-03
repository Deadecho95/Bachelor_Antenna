#ifndef FACTORY_H
#define FACTORY_H

#ifdef __cplusplus


	class Factory
	{
		public:
			Factory();
		
			static void init();
			static void build();
	};
	
#endif //cplusplus
	
	
#ifdef __cplusplus
	extern "C" {
#endif
		
void Factory_init();
void Factory_build();
		
#ifdef __cplusplus
	}
#endif //cplusplus
#endif //factory_H

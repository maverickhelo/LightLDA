#include "common.h"

#include <cstring>

namespace multiverso { namespace lightlda 
{
    const int64_t kMB = 1024 * 1024;

    // -- Begin: Config definitioin and defalut values --------------------- //
    int32_t Config::num_vocabs = -1;
    int32_t Config::num_topics = 100;
    int32_t Config::num_iterations = 100;
    int32_t Config::mh_steps = 2;
    int32_t Config::num_servers = 1;
    int32_t Config::num_local_workers = 1;
    int32_t Config::num_aggregator = 1;
    int32_t Config::num_blocks = 1;
    int64_t Config::max_num_document = -1;
    float Config::alpha = 0.01f;
    float Config::beta = 0.01f;
    std::string Config::server_file = "";
    std::string Config::input_dir = "";
    bool Config::warm_start = false;
    bool Config::inference = false;
    bool Config::out_of_core = false;
    int64_t Config::data_capacity = 1024 * kMB;
    int64_t Config::model_capacity = 512 * kMB;
    int64_t Config::delta_capacity = 256 * kMB;
    int64_t Config::alias_capacity = 512 * kMB;
    float Config::laplace_scale = 1.0;
    float Config::laplace_upperthres = 0.1;
    float Config::laplace_lowerthres = 0.0;
    int32_t Config::max_noise_num = 2;
    int32_t Config::is_print = 0;
    int32_t Config::laplace_steps = 1000;
    int32_t Config::is_noised = 0;
    // -- End: Config definitioin and defalut values ----------------------- //

    void Config::Init(int argc, char* argv[])
    {
        if (argc < 2)
        {
            PrintUsage();
        }
        for (int i = 1; i < argc; ++i)
        {
            if (strcmp(argv[i], "-help") == 0 || strcmp(argv[i], "--help") == 0)
            {
                PrintUsage();
            }
            if (strcmp(argv[i], "-num_vocabs") == 0) num_vocabs = atoi(argv[i + 1]);
            if (strcmp(argv[i], "-num_topics") == 0) num_topics = atoi(argv[i + 1]);
            if (strcmp(argv[i], "-num_iterations") == 0) num_iterations = atoi(argv[i + 1]);
            if (strcmp(argv[i], "-mh_steps") == 0) mh_steps = atoi(argv[i + 1]);
            if (strcmp(argv[i], "-num_servers") == 0) num_servers = atoi(argv[i + 1]);
            if (strcmp(argv[i], "-num_local_workers") == 0) num_local_workers = atoi(argv[i + 1]);
            if (strcmp(argv[i], "-num_aggregator") == 0) num_aggregator = atoi(argv[i + 1]);
            if (strcmp(argv[i], "-num_blocks") == 0) num_blocks = atoi(argv[i + 1]);
            if (strcmp(argv[i], "-max_num_document") == 0) max_num_document = atoll(argv[i + 1]);
            if (strcmp(argv[i], "-alpha") == 0) alpha = static_cast<float>(atof(argv[i + 1]));
            if (strcmp(argv[i], "-beta") == 0) beta = static_cast<float>(atof(argv[i + 1]));
            if (strcmp(argv[i], "-input_dir") == 0) input_dir = std::string(argv[i + 1]);
            if (strcmp(argv[i], "-server_file") == 0) server_file = std::string(argv[i + 1]);
            if (strcmp(argv[i], "-warm_start") == 0) warm_start = true;
            if (strcmp(argv[i], "-out_of_core") == 0) out_of_core = true;
            if (strcmp(argv[i], "-data_capacity") == 0) data_capacity = atoi(argv[i + 1]) * kMB;
            if (strcmp(argv[i], "-model_capacity") == 0) model_capacity = atoi(argv[i + 1]) * kMB;
            if (strcmp(argv[i], "-alias_capacity") == 0) alias_capacity = atoi(argv[i + 1]) * kMB;
            if (strcmp(argv[i], "-delta_capacity") == 0) delta_capacity = atoi(argv[i + 1]) * kMB;            
            if (strcmp(argv[i], "-laplace_scale") == 0) laplace_scale = static_cast<float>(atof(argv[i + 1]));
            if (strcmp(argv[i], "-laplace_lowerthres") == 0) laplace_lowerthres = static_cast<float>(atof(argv[i + 1]));
            if (strcmp(argv[i], "-laplace_upperthres") == 0) laplace_upperthres = static_cast<float>(atof(argv[i + 1]));
            if (strcmp(argv[i], "-max_noise_num") == 0) max_noise_num = atoi(argv[i + 1]);
            if (strcmp(argv[i], "-is_print") == 0) is_print = atoi(argv[i + 1]);
            if (strcmp(argv[i], "-laplace_steps") == 0) laplace_steps = atoi(argv[i + 1]);
            if (strcmp(argv[i], "-is_noised") == 0) is_noised = atoi(argv[i + 1]);
        }
        Check();
    }

    void Config::PrintTrainingUsage()
    {
        printf("LightLDA usage: \n");
        printf("-num_vocabs <arg>        Size of dataset vocabulary \n");
        printf("-num_topics <arg>        Number of topics. Default: 100\n");
        printf("-num_iterations <arg>    Number of iteratioins. Default: 100\n");
        printf("-mh_steps <arg>          Metropolis-hasting steps. Default: 2\n");
        printf("-alpha <arg>             Dirichlet prior alpha. Default: 0.1\n");
        printf("-beta <arg>              Dirichlet prior beta. Default: 0.01\n\n");
        printf("-num_blocks <arg>        Number of blocks in disk. Default: 1\n");
        printf("-max_num_document <arg>  Max number of document in a data block \n");
        printf("-input_dir <arg>         Directory of input data, containing\n");
        printf("                         files generated by dump_block \n\n");
        printf("-num_servers <arg>       Number of servers. Default: 1\n");
        printf("-num_local_workers <arg> Number of local training threads. Default: 4\n");
        printf("-num_aggregator <arg>    Number of local aggregation threads. Default: 1\n");
        printf("-server_file <arg>       Server endpoint file. Used by MPI-free version\n"); 
        printf("-warm_start              Warm start \n");
        printf("-out_of_core             Use out of core computing \n\n");
        printf("-data_capacity <arg>     Memory pool size(MB) for data storage, \n");
        printf("                         should larger than the any data block\n");
        printf("-model_capacity <arg>    Memory pool size(MB) for local model cache\n");
        printf("-alias_capacity <arg>    Memory pool size(MB) for alias table \n");
        printf("-delta_capacity <arg>    Memory pool size(MB) for local delta cache\n\n");
        printf("-is_noised <arg>         Noised or not. Default: 0\n");
        printf("-laplace_scale <arg>     Laplace distribution scala. Default: 0.1\n");
        printf("-laplace_lowerthres <arg> Laplace lower threshold. Default: 0.0\n");
        printf("-laplace_upperthres <arg> Laplace upper threshold. Default: 0.1\n");
        printf("-max_noise_num <arg>     Document max noise words num per positon. Default: 1000\n");
        printf("-is_print <arg>          Print or not. Default: 0\n");
        printf("-laplace_steps <arg>     Laplace sample steps. Default: 1000\n");
        exit(0);
    }

    void Config::PrintInferenceUsage()
    {
        printf("LightLDA Inference usage: \n");
        printf("-num_vocabs <arg>        Size of dataset vocabulary \n");
        printf("-num_topics <arg>        Number of topics. Default: 100\n");
        printf("-num_iterations <arg>    Number of iteratioins. Default: 100\n");
        printf("-mh_steps <arg>          Metropolis-hasting steps. Default: 2\n");
        printf("-alpha <arg>             Dirichlet prior alpha. Default: 0.1\n");
        printf("-beta <arg>              Dirichlet prior beta. Default: 0.01\n\n");
        printf("-num_blocks <arg>        Number of blocks in disk. Default: 1\n");
        printf("-max_num_document <arg>  Max number of document in a data block \n");
        printf("-input_dir <arg>         Directory of input data, containing\n");
        printf("                         files generated by dump_block \n\n");
        printf("-num_local_workers <arg> Number of local training threads. Default: 4\n");
        printf("-warm_start              Warm start \n");
        printf("-out_of_core             Use out of core computing \n\n");
        printf("-data_capacity <arg>     Memory pool size(MB) for data storage, \n");
        printf("                         should larger than the any data block\n");
        exit(0);
    }

    void Config::PrintUsage()
    {
        if(!inference)
        {
            PrintTrainingUsage();
        }
        else
        {
            PrintInferenceUsage();
        }
    }

    void Config::Check()
    {
        if (input_dir == "" || num_vocabs <= 0 || max_num_document == -1) 
        {
            PrintUsage();
        }
    }
} // namespace lightlda
} // namespace multiverso

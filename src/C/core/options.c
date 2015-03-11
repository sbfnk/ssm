/**************************************************************************
 *    This file is part of ssm.
 *
 *    ssm is free software: you can redistribute it and/or modify it
 *    under the terms of the GNU General Public License as published
 *    by the Free Software Foundation, either version 3 of the
 *    License, or (at your option) any later version.
 *
 *    ssm is distributed in the hope that it will be useful, but
 *    WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public
 *    License along with ssm.  If not, see
 *    <http://www.gnu.org/licenses/>.
 *************************************************************************/

#include "ssm.h"


struct opts_part{
    char *s;
    int val;
    char *l;
    char *description;
    int has_arg;
    ssm_algo_t algo;
};


void ssm_options_load(ssm_options_t *opts, ssm_algo_t algo, int argc, char *argv[])
{
    opts->algo = algo;
    
    struct opts_part all_opts[] = {
        {"D", 'D', "dt",             "integration time step", required_argument,  SSM_WORKER | SSM_SMC | SSM_KALMAN | SSM_KMCMC | SSM_PMCMC | SSM_KSIMPLEX | SSM_SIMPLEX | SSM_MIF | SSM_SIMUL },
        {"I", 'I', "id",             "general id (unique integer identifier that will be appended to the output)", required_argument,  SSM_WORKER | SSM_SMC | SSM_KALMAN | SSM_KMCMC | SSM_PMCMC | SSM_KSIMPLEX | SSM_SIMPLEX | SSM_MIF | SSM_SIMUL },
        {"P", 'P', "root",           "root path for output files (if any) (no trailing slash)", required_argument,  SSM_SMC | SSM_KALMAN | SSM_KMCMC | SSM_PMCMC | SSM_KSIMPLEX | SSM_SIMPLEX | SSM_MIF | SSM_SIMUL },
        {"X", 'X', "next",           "write the outputed parameters in a file prefixed by the argument", required_argument,  SSM_WORKER | SSM_SMC | SSM_KALMAN | SSM_KMCMC | SSM_PMCMC | SSM_KSIMPLEX | SSM_SIMPLEX | SSM_MIF | SSM_SIMUL },
        {"N", 'N', "n_thread",       "number of threads to be used", required_argument,  SSM_SMC | SSM_PMCMC | SSM_MIF | SSM_SIMUL },
        {"J", 'J', "n_parts",        "number of particles", required_argument,  SSM_SMC | SSM_PMCMC | SSM_MIF | SSM_SIMUL },
        {"O", 'O', "n_obs",          "number of observations to be fitted (for tempering)", required_argument,  SSM_SMC | SSM_KALMAN | SSM_KMCMC | SSM_PMCMC | SSM_KSIMPLEX | SSM_SIMPLEX | SSM_MIF },
        {"A", 'A', "cooling",        "cooling factor (for sampling covariance live tuning or MIF cooling)", required_argument, SSM_KMCMC | SSM_PMCMC | SSM_MIF },
        {"C", 'C', "switch",         "select switching iteration from initial covariance to empirical one (mcmc) or to update formula introduced in Ionides et al. 2006 (mif)", required_argument,  SSM_KMCMC | SSM_PMCMC | SSM_MIF },
        {"W", 'W', "eps_switch",     "select number of burnin iterations before tuning epsilon", required_argument,  SSM_KMCMC | SSM_PMCMC },
        {"T", 'T', "n_traj",         "number of trajectories stored", required_argument,  SSM_KMCMC | SSM_PMCMC },
        {"M", 'M', "iter",           "number of iterations", required_argument,  SSM_KMCMC | SSM_PMCMC | SSM_KSIMPLEX | SSM_SIMPLEX | SSM_MIF },
        {"B", 'B', "start",          "ISO 8601 date when simulation starts", required_argument,  SSM_SIMUL },
        {"E", 'E', "end",            "ISO 8601 date when simulation end", required_argument,  SSM_SIMUL },
        {"Y", 'Y', "eps_abs_integ",  "absolute error for adaptive step-size control", required_argument,  SSM_WORKER | SSM_SMC | SSM_KALMAN | SSM_KMCMC | SSM_PMCMC | SSM_KSIMPLEX | SSM_SIMPLEX | SSM_MIF | SSM_SIMUL },
        {"Z", 'Z', "eps_rel_integ",  "relative error for adaptive step-size control", required_argument,  SSM_WORKER | SSM_SMC | SSM_KALMAN | SSM_KMCMC | SSM_PMCMC | SSM_KSIMPLEX | SSM_SIMPLEX | SSM_MIF | SSM_SIMUL },
        {"G", 'G', "freeze_forcing", "freeze covariates to their value at specified ISO 8601 date", required_argument, SSM_WORKER |  SSM_SMC | SSM_KALMAN | SSM_KMCMC | SSM_PMCMC | SSM_KSIMPLEX | SSM_SIMPLEX | SSM_MIF | SSM_SIMUL },
        {"K", 'K', "like_min",       "if applicable, particles with likelihood smaller than like_min are considered lost. Otherwise, lower bound on likelihood", required_argument,  SSM_WORKER | SSM_SMC | SSM_KALMAN | SSM_KMCMC | SSM_PMCMC | SSM_KSIMPLEX | SSM_SIMPLEX | SSM_MIF },
        {"U", 'U', "eps_max",        "maximum value allowed for epislon", required_argument,  SSM_KMCMC | SSM_PMCMC },
        {"S", 'S', "alpha",          "smoothing factor of exponential smoothing used to compute smoothed acceptance rate (low values increase degree of smoothing)", required_argument,  SSM_KMCMC | SSM_PMCMC },
        {"H", 'H', "heat",           "re-heating accross MIF iterations (scales standard deviation of proposals)", required_argument,  SSM_MIF },
        {"L", 'L', "lag",            "lag for fixed-lag smoothing (proportion of the data)", required_argument,  SSM_MIF },
        {"F", 'F', "freq",           "For simulations outside the data range, print the outputs (and reset incidences to 0 if any) every specified days", required_argument,  SSM_WORKER | SSM_SIMUL },
        {"V", 'V', "size",           "simplex size used as stopping criteria", required_argument,  SSM_KSIMPLEX | SSM_SIMPLEX },
        {"Q", 'Q', "interpolator",   "gsl interpolator for covariates", required_argument,  SSM_WORKER | SSM_SMC | SSM_KALMAN | SSM_KMCMC | SSM_PMCMC | SSM_KSIMPLEX | SSM_SIMPLEX | SSM_MIF | SSM_SIMUL },
        {"R", 'R', "server",         "domain name or IP address of the particule server (e.g 127.0.0.1)", required_argument,  SSM_WORKER },

        {"h", 'h', "help",           "print the usage on stdout", no_argument,  SSM_WORKER | SSM_SMC | SSM_KALMAN | SSM_KMCMC | SSM_PMCMC | SSM_KSIMPLEX | SSM_SIMPLEX | SSM_MIF | SSM_SIMUL },
        {"v", 'v', "verbose",        "print logs (verbose)", no_argument,  SSM_WORKER | SSM_SMC | SSM_KALMAN | SSM_KMCMC | SSM_PMCMC | SSM_KSIMPLEX | SSM_SIMPLEX | SSM_MIF | SSM_SIMUL },
        {"n", 'n', "warning",        "print warnings", no_argument,  SSM_WORKER | SSM_SMC | SSM_KALMAN | SSM_KMCMC | SSM_PMCMC | SSM_KSIMPLEX | SSM_SIMPLEX | SSM_MIF | SSM_SIMUL },
        {"d", 'd', "no_dem_sto",     "turn off demographic stochasticity  (if any)", no_argument,  SSM_WORKER | SSM_SMC | SSM_KALMAN | SSM_KMCMC | SSM_PMCMC | SSM_KSIMPLEX | SSM_SIMPLEX | SSM_MIF | SSM_SIMUL },
        {"w", 'w', "no_white_noise", "turn off white noises (if any)", no_argument,  SSM_WORKER | SSM_SMC | SSM_KALMAN | SSM_KMCMC | SSM_PMCMC | SSM_KSIMPLEX | SSM_SIMPLEX | SSM_MIF | SSM_SIMUL },
        {"f", 'f', "no_diff",        "turn off diffusions (if any)", no_argument,  SSM_WORKER | SSM_SMC | SSM_KALMAN | SSM_KMCMC | SSM_PMCMC | SSM_KSIMPLEX | SSM_SIMPLEX | SSM_MIF | SSM_SIMUL },
        {"t", 't', "traj",           "print the trajectories", no_argument,  SSM_SMC | SSM_KALMAN | SSM_MIF | SSM_SIMUL| SSM_PMCMC | SSM_KMCMC },
        {"r", 'r', "no_filter",      "do not filter", no_argument,  SSM_SMC },
        {"c", 'c', "trace",          "print the traces", no_argument,  SSM_SMC | SSM_KALMAN | SSM_KMCMC | SSM_PMCMC | SSM_KSIMPLEX | SSM_SIMPLEX | SSM_MIF },
        {"x", 'x', "hat",            "print the state estimates", no_argument,  SSM_SMC | SSM_KALMAN | SSM_SIMUL | SSM_PMCMC | SSM_KMCMC  },
        {"e", 'e', "diag",           "print the diagnostics outputs (prediction residuals...)", no_argument,  SSM_SMC | SSM_KALMAN | SSM_MIF },
        {"p", 'p', "prior",          "add log(prior) to the estimated loglikelihood", no_argument,  SSM_SMC | SSM_KALMAN | SSM_KSIMPLEX | SSM_SIMPLEX | SSM_MIF },
        {"s", 's', "smooth",         "tune epsilon with the value of the acceptance rate obtained with exponential smoothing", no_argument,  SSM_KMCMC | SSM_PMCMC },
        {"a", 'a', "acc",            "print the acceptance rate", no_argument,  SSM_KMCMC | SSM_PMCMC },
        {"z", 'z', "tcp",            "dispatch particles across machines", no_argument,  SSM_SIMUL | SSM_SMC | SSM_PMCMC | SSM_MIF },
        {"b", 'b', "ic_only",        "only fit the initial condition using fixed lag smoothing", no_argument,  SSM_MIF },
        {"l", 'l', "least_squares",  "minimize the sum of squared errors instead of maximizing the likelihood", no_argument,  SSM_SIMPLEX },
        {"g", 'g', "seed_time",      "seed the random number generator with the current time", no_argument,  SSM_WORKER | SSM_SMC | SSM_KALMAN | SSM_KMCMC | SSM_PMCMC | SSM_KSIMPLEX | SSM_SIMPLEX | SSM_MIF | SSM_SIMUL },
        {"o", 'o', "no-proposal",    "don't vary proposal (for tuning)", no_argument,  SSM_KMCMC | SSM_PMCMC }
    };

    int i;
    int n_all_opts = sizeof(all_opts)/sizeof(*all_opts);
    int n_opts = 0;
    for(i=0; i< n_all_opts; i++){
        if(all_opts[i].algo & algo) n_opts++;
    }

    char shortopts[SSM_STR_BUFFSIZE] = "";
    char help_msg[SSM_BUFFER_SIZE] = "";
    struct option long_options[n_opts+1];

    int j=0;
    for(i=0; i< n_all_opts; i++){
        if(all_opts[i].algo & algo){
            strcat(shortopts, all_opts[i].s);
            if(all_opts[i].has_arg == required_argument){
                strcat(shortopts, ":");
            }

            snprintf(help_msg, SSM_BUFFER_SIZE, "%s-%s, --%-20s %s\n", help_msg, all_opts[i].s, all_opts[i].l, all_opts[i].description);

            long_options[j].name = all_opts[i].l;
            long_options[j].has_arg = all_opts[i].has_arg;
            long_options[j].flag = NULL;
            long_options[j].val = all_opts[i].val;
            j++;
        }
    }

    long_options[n_opts].name = NULL;
    long_options[n_opts].has_arg = 0;
    long_options[n_opts].flag = NULL;
    long_options[n_opts].val = 0;

    int c;

    while (1) {
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, shortopts, long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1) break;
        switch (c) {
        case 0:
            /* If this option set a flag, do nothing else now. */
            if (long_options[option_index].flag != 0) {
                break;
            }
            break;

        case 'h':
            printf("%s", help_msg);
            exit(EXIT_SUCCESS);


        case 'D': //dt
            opts->dt = atof(optarg);
            break;

        case 'I': //id
            opts->id = atoi(optarg);
            break;

        case 'P': //root path
            strncpy(opts->root, optarg, SSM_STR_BUFFSIZE);
            break;

	case 'X': //next
            strncpy(opts->next, optarg, SSM_STR_BUFFSIZE);
            break;

        case 'N': //n_thread
            opts->n_thread = atoi(optarg);
            break;

        case 'J': //n_parts
            opts->J = atoi(optarg);
            break;

        case 'O': //n_obs
            opts->n_obs = atoi(optarg);
            break;

        case 'A': //cooling
            opts->a = atof(optarg);
            break;

        case 'C': //switch
            opts->m_switch = atoi(optarg);
            break;

        case 'W': //eps_switch
            opts->eps_switch = atoi(optarg);
            break;

        case 'T': //n_traj
            opts->n_traj = atoi(optarg);
            break;

        case 'M': //iter
            opts->n_iter = atoi(optarg);
            break;

        case 'B': //start
            strncpy(opts->start, optarg, SSM_STR_BUFFSIZE);
            break;

        case 'E': //end
            strncpy(opts->end, optarg, SSM_STR_BUFFSIZE);
            break;

        case 'Y': //eps_abs_integ
            opts->eps_abs = atof(optarg);
            break;

        case 'Z': //eps_rel_integ
            opts->eps_rel = atof(optarg);
            break;

        case 'G': //freeze_forcing
            strncpy(opts->freeze_forcing, optarg, SSM_STR_BUFFSIZE);
            break;

        case 'K': //like_min
            opts->like_min = atof(optarg);
            break;

        case 'U': //eps_max
            opts->eps_max = atof(optarg);
            break;

        case 'S': //alpha
            opts->alpha = atof(optarg);
            break;

        case 'H': //heat
            opts->b = atof(optarg);
            break;

        case 'L': //lag
            opts->L = atof(optarg);
            break;

        case 'F': //freq
            opts->freq = atoi(optarg);
            break;

        case 'V': //size
            opts->size_stop = atof(optarg);
            break;

        case 'Q': //interpolator
            strncpy(opts->interpolator, optarg, SSM_STR_BUFFSIZE);
            break;

        case 'R': //server
            strncpy(opts->server, optarg, SSM_STR_BUFFSIZE);
            break;

        case 'n': //warning
            opts->print |= SSM_PRINT_WARNING;
            break;

        case 'v': //verbosity
            opts->print |= SSM_PRINT_LOG;
            break;

        case 'd': //no_dem_sto
            opts->noises_off |= SSM_NO_DEM_STO;
            break;

        case 'w': //no_white_noise
            opts->noises_off |= SSM_NO_WHITE_NOISE;
            break;

        case 'f': //no_diff
            opts->noises_off |= SSM_NO_DIFF;
            break;

        case 't': //traj
            opts->print |= SSM_PRINT_X;
            break;

        case 'r': //no_filter
            opts->flag_no_filter = 1;
            break;

        case 'c': //trace
            opts->print |= SSM_PRINT_TRACE;
            break;

        case 'x': //hat
            opts->print |= SSM_PRINT_HAT;
            break;

        case 'e': //diag
            opts->print |= SSM_PRINT_DIAG;
            break;

        case 'p': //prior
            opts->flag_prior = 1;
            break;

        case 's': //smooth
            opts->flag_smooth = 1;
            break;

        case 'a': //acc
            opts->print |= SSM_PRINT_DIAG;
            break;

        case 'z': //tcp
            opts->flag_tcp = 1;
            break;

        case 'b': //ic_only
            opts->flag_ic_only = 1;
            break;

        case 'l': //least_squares
            opts->flag_least_squares = 1;
            break;

        case 'g': //seed_time"
            opts->flag_seed_time = 1;
            break;

        case 'o': //no-proposal
            opts->flag_no_proposal = 1;
            break;

        case '?':
            exit(EXIT_FAILURE);

        default:
            abort();
        }
    }

    argc -= optind;
    argv += optind;

    ssm_options_set_implementation(opts, algo, argc, argv);    
}

void ssm_options_set_implementation(ssm_options_t *opts, ssm_algo_t algo, int argc, char *argv[])
{
    if(algo & SSM_WORKER){
	if(argc != 2){
	    ssm_print_err("invalid usage, correct usage is: worker <implementation> <algorithm> [options]");
	    exit(EXIT_FAILURE);
	} else {
	    
	    if(!strcmp(argv[1], "smc")){
		opts->worker_algo = SSM_SMC;
	    } else if (!strcmp(argv[1], "mif")){
		opts->worker_algo = SSM_MIF;
	    } else if (!strcmp(argv[1], "pmcmc")){
		opts->worker_algo = SSM_PMCMC;
	    } else if (!strcmp(argv[1], "simul")){
		opts->worker_algo = SSM_SIMUL;
	    } else {
		ssm_print_err("worker algorithm has to be either smc, mif, pmcmc or simul");
		exit(EXIT_FAILURE);
	    }
	}
    }

    //constraints methods
    if ( algo & (SSM_KALMAN | SSM_KSIMPLEX | SSM_KMCMC) ){

	if(argc == 0 || !strcmp(argv[0], "sde")){
	    opts->implementation = SSM_EKF;
	} else {
            ssm_print_err("invalid implementation");
            exit(EXIT_FAILURE);	    
	}

    } else if (algo & SSM_SIMPLEX) { 

	if(argc == 0 || !strcmp(argv[0], "ode")){
	    opts->implementation = SSM_ODE;
	} else {
            ssm_print_err("invalid implementation");
            exit(EXIT_FAILURE);	    
	}

    } else {
     
	//non constraints methods
	if(argc == 0) {	
	    opts->implementation = SSM_ODE; 
	} else {

	    if (!strcmp(argv[0], "ode")) {
		opts->implementation = SSM_ODE;
	    } else if (!strcmp(argv[0], "sde")) {
		opts->implementation = SSM_SDE;
	    } else if (!strcmp(argv[0], "psr")) {
		opts->implementation = SSM_PSR;
	    } else {
		ssm_print_err("invalid implementation");
		exit(EXIT_FAILURE);
	    }
	}
    }

    //force correct noises_off for implementation
    if(opts->implementation == SSM_ODE){
	opts->noises_off |=  SSM_NO_DEM_STO | SSM_NO_WHITE_NOISE | SSM_NO_DIFF;
    }
}

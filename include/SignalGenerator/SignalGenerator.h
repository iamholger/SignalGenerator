#pragma once
#include <iostream>
#include "AppEval.h"
#include "Eigen/Eigen"

using namespace Apprentice;
using namespace Eigen;

namespace SignalGenerator
{

  struct MyConfig
  {
    int num_detectors;
    int num_bins_detector_block;
    int num_channels;
    int num_bins_detector_block_compressed;
    int num_bins_mode_block_compressed;
    int num_bins_total_compressed;
    std::vector<int> num_bins;
    std::vector<int> num_subchannels;
    std::vector<std::vector<int> > subchannel_osc_patterns; 
  };


  class SignalGenerator
  {
     public:
        SignalGenerator(
              AppEval  sinsq,
              AppEval  sin,
              VectorXd const core,
              MyConfig const  conf
              ) : _sinsq(sinsq), _sin(sin), _core(core), _conf(conf) {}

     VectorXd predict(VectorXd const & x, int oscmode);
    
     void printConfig();

     VectorXd Oscillate(VectorXd const & sf_sinsq, VectorXd const & sf_sin, double Ue, double Um, int oscmode);

     private:
        AppEval _sinsq;
        AppEval _sin;
        VectorXd const _core;
        MyConfig const _conf;
  };
};

#include "SignalGenerator.h"

VectorXd SignalGenerator::SignalGenerator::predict(VectorXd const & x, int oscmode)
{
    auto const SINSQ   = _sinsq.eval(x.segment(0,1));
    auto const SIN     =   _sin.eval(x.segment(0,1));
    return _core + Oscillate(SINSQ, SIN, x[1], pow(10, x[2]), oscmode);
}

VectorXd SignalGenerator::SignalGenerator::Oscillate(VectorXd const & sf_sinsq, VectorXd const & sf_sin, double Ue, double Um, int oscmode)
{

    double prob_mumu(0), prob_ee(0), prob_mue(0), prob_mue_sq(0), prob_muebar(0), prob_muebar_sq(0);

    // TODO Make this logic nice
    if (oscmode==0) {
       prob_mue_sq    = 4*Ue*Ue*Um*Um;
       prob_muebar_sq = prob_mue_sq;  
    }
    else if (oscmode==1) prob_mumu =  -4.0 * (1.0 - Um*Um) * Um*Um;
    else
    {
       std::cerr << "oscillation mode has to be either 0 or 1: " <<oscmode << "\n";
       exit(1);
    }

    VectorXd retVec = VectorXd::Zero(_core.rows());

    double osc_amp(0), osc_amp_sq(0);
    int osc_pattern(0);
    size_t offset(0);
    // Iterate over channels
    for (int i=0; i<_conf.num_channels; i++)
    {
      size_t nbins_chan = _conf.num_bins[i];
      auto const & thisPattern = _conf.subchannel_osc_patterns[i];
      // Iterate over subchannels
      for (int j=0; j<_conf.num_subchannels[i]; j++)
      {
        osc_pattern = thisPattern[j];
        switch (osc_pattern)
        {
          case 11:
                osc_amp_sq = prob_ee;
                osc_amp = 0;
                break;
            case -11:
                osc_amp_sq = prob_ee;
                osc_amp = 0;
                break;
            case 22:
                osc_amp_sq = prob_mumu;
                osc_amp = 0;
                break;
            case -22:
                osc_amp_sq = prob_mumu;
                osc_amp = 0;
                break;
            case 21:
                osc_amp    = prob_mue;
                osc_amp_sq = prob_mue_sq;
                break;
            case -21:
                osc_amp    = prob_muebar;
                osc_amp_sq = prob_muebar_sq;
                break;
            case 0:  // TODO ask Mark about actual logic
                osc_amp = 0;
                osc_amp_sq = 0;
            default:
                break;
        }

       // Iterate over detectors
       for (int d=0; d<_conf.num_detectors;++d)
       {
         size_t first  = d*_conf.num_bins_detector_block + offset;
         retVec.segment(first, nbins_chan).noalias() += osc_amp   *  sf_sin.segment(first, nbins_chan);
         retVec.segment(first, nbins_chan).noalias() += osc_amp_sq*sf_sinsq.segment(first, nbins_chan);
       }
       offset +=nbins_chan;
      }
    }
    return retVec;
}


void SignalGenerator::SignalGenerator::printConfig ()
{
    std::cerr << "_conf.num_channels " << _conf.num_channels << "\n";
    for (int i=0; i<_conf.num_channels; i++)
        std::cerr <<  "\t_conf.num_bins["<<i<<"] " << _conf.num_bins[i] <<"\n";
   
   
    for (int i=0; i<_conf.num_channels; i++)
        std::cerr <<  "\t_conf.num_subchannels["<<i<<"] " << _conf.num_subchannels[i] <<"\n";
    
    for (int i=0; i<_conf.num_channels; i++) 
    {
         for (int j=0; j<_conf.num_subchannels[i]; j++)
           std::cerr <<  "\t\t_conf.subchannel_osc_patterns["<<i<<"]["<<j<<"] " << _conf.subchannel_osc_patterns[i][j] <<"\n";
    }
   
    std::cerr << "_conf.num_detectors " << _conf.num_detectors << "\n";
    std::cerr << "_conf.num_bins_detector_block " << _conf.num_bins_detector_block << "\n";
}

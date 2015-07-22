#ifndef __HWSTUB_H__
#define __HWSTUB_H__
#define _USE_MATH_DEFINES

#include <iomanip>
class HwStub;
class HwStub{
    
 public:    

  
    
  HwStub(
	       int hwPhiS=0,
	       int hwRt=0,
	       int hwZ=0,
	       int hwDphi=0,
         int hwSegment=0,
         int hwRho=0,
         double phi =0.,
         double r=0.,
         double z=0.
         );
    
  ~HwStub();

  
  void setPhiS( int et) { hwPhiS_ =et ;}
  void setRt( int et ) { hwRt_ = et;}
  void setZ( int et ) { hwZ_ = et;}
  void setBend( int et ) { hwBend_ = et;}
  void setDphi( int et ) { hwDphi_ = et;}
  void setSegment(int et) { hwSegment_ = et;}
  void setRho(int et) { hwRho_ = et;}
  void setDoubleZ( double et ) { z_ = et;}
  void setDoubleR( double et ) { r_ = et;}
  void setDoublePhi( double et ) { phi_ = et;}
  void setDoubleBend( double et ) { bend_ = et;}
  void setDoubleDphi( double et) { dphi_ = et;}
  void setRerr(double et) { rErr_ = et;}
  
  int hwPhiS()           const{   return hwPhiS_;    }
  int hwZ()              const{   return hwZ_;       }
  int hwBend()           const{   return hwBend_;    }
  int hwRt()             const{   return hwRt_;      }
  int hwDphi()           const{   return hwRho_;     }
  int hwSegment()        const{   return hwSegment_; }
  int hwRho()            const{   return hwRho_;     }
  double z()             const{   return z_;         }
  double r()             const{   return r_;         }
  double phi()           const{   return phi_;       }
  double dphi()          const{   return dphi_;      }
  double bend()          const{   return bend_;      }


  std::pair <float, float>trkPhiAtR(float et) const;
 private:
  
  
  int hwPhiS_;
  int hwRt_;
  int hwZ_; 
  int hwBend_;
  int hwDphi_;
  int hwSegment_;
  int hwRho_;
  double phi_;
  double dphi_;
  double r_;
  double z_;
  double rErr_;
  double bend_;
  
};
  


#endif

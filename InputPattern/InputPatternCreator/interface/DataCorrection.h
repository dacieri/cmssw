#ifndef __DATACORRECTION_H__
#define __DATACORRECTION_H__
/*
 * Implementation of reduced bits for the bend information.
https://indico.cern.ch/event/350910/session/4/contribution/12/material/slides/0.pdf
https://indico.cern.ch/event/361219/session/7/contribution/17/material/slides/5.pdf
3 bits for PS, 4 bits for 2S.
*/
static double ConvertBarrelBend( double bend, unsigned int layer ){

//	std::cout << "Layer " << layer << std::endl;
	double value(bend), b(fabs(bend));
	int s = ( bend > 0 ) ? 1 : -1;

	switch( layer ){
		case 1:
		case 2:
		case 3:
			if( b <= 0.5 ) value = 0;
			else if( 1.5 <= b && b <= 2 ) value = s * 1.75;
			break;
		case 4:
			if( b <= 0.5 ) value = 0;
			break;
		case 5:
			if( b <= 0.5 ) value = 0;
			else if( 1.5 <= b && b <= 2.5 ) value = s * 2;
			else if( 3.0 <= b && b <= 3.5 ) value = s * 3.25;
			break;
		case 6:
			if( b <= 0.5 ) value = 0;
			else if( 1.5 <= b && b <= 2.5 ) value = s * 2;
			else if( 3.0 <= b && b <= 4.0 ) value = s * 3.5;
			else if( 4.5 <= b && b <= 5.0 ) value = s * 4.75;
			break;
		default:
			break;
	}
	return value;
}

static double ConvertEndcapBend( double bend, unsigned int ring ){

//	std::cout << "Ring " << ring << std::endl;
	double value(bend), b(fabs(bend));
	int s = ( bend > 0 ) ? 1 : -1;

	switch( ring ){
		case 1:
		case 2:
		case 3:
		case 4:
			if( b <= 0.5 ) value = 0;
			break;
		case 5:
		case 6:
		case 7:
			if( b <= 1.0 ) value = 0;
			break;
		case 8:
			if( b <= 1.0 ) value = 0;
			else if( 1.5 <= b && b <= 2.0 ) value = s * 1.75;
			break;
		case 9:
			if( b <= 1.0 ) value = 0;
			else if( 1.5 <= b && b <= 2.0 ) value = s * 1.75;
			else if( 2.5 <= b && b <= 3.0 ) value = s * 2.75;
			break;
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			if( b <= 0.5 ) value = 0;
			else if( 1.5 <= b && b <= 2.0 ) value = s * 1.75;
			else if( 2.5 <= b && b <= 3.0 ) value = s * 2.75;
			else if( 3.5 <= b && b <= 4.0 ) value = s * 3.75;
			break;
		default:
			break;
	}
	return value;
}


#endif


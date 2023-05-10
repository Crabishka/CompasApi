// ConsoleApi.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#import "C:\\Program Files\\ASCON\\KOMPAS-3D v21 Study\\Bin\\kAPI5.tlb"
#import "C:\Program Files\ASCON\KOMPAS-3D v21 Study\Bin\ksConstants3D.tlb"


using namespace Kompas6API5;
using namespace Kompas6Constants3D;


void createCap(Kompas6API5::KompasObjectPtr kompas) {
    Kompas6API5::ksDocument3DPtr doc;
    doc = kompas->Document3D();
    doc->Create(false, true);
    doc = kompas->ActiveDocument3D();

    kompas->Visible = true;

    ksPartPtr Part;
    Part = doc->GetPart(Kompas6Constants3D::pTop_Part);

    ksEntityPtr sketch = Part->NewEntity(o3d_sketch);
    ksSketchDefinitionPtr sketchDef = sketch->GetDefinition();
    sketchDef->SetPlane(Part->GetDefaultEntity(o3d_planeXOY));
    sketch->Create();
    ksDocument2DPtr doc2D = sketchDef->BeginEdit();
    doc2D->ksLineSeg(0, 0, 2, 0, 3);

    doc2D->ksLineSeg(0, 5, 2, 5, 1);
    doc2D->ksLineSeg(0, 5, 0, 30.5, 1);
    doc2D->ksLineSeg(0, 30.5, -18, 30.5, 1);
    doc2D->ksLineSeg(-18, 30.5, -18, 32.5, 1);
    doc2D->ksLineSeg(-18, 32.5, 2, 32.5, 1);
    doc2D->ksLineSeg(2, 32.5, 2, 5, 1);


    sketchDef->EndEdit();
    // выдавливание крышки
    ksEntityPtr rot = Part->NewEntity(o3d_bossRotated);
    ksBossRotatedDefinitionPtr rotDef = rot->GetDefinition();
    rotDef->SetSideParam(TRUE, 360);
    rotDef->directionType* (Kompas6Constants3D::dtNormal);
    rotDef->SetSketch(sketch);
    rot->Create();
    // фаска
    ksEntityPtr cham = Part->NewEntity(o3d_chamfer);
    ksChamferDefinitionPtr chamDef = cham->GetDefinition();
    chamDef->tangent = FALSE;
    chamDef->SetChamferParam(FALSE, 1, 1);
    ksEntityCollectionPtr enColPart = Part->EntityCollection(o3d_edge);
    ksEntityCollectionPtr EnColChamfer = chamDef->array();
    EnColChamfer->Clear();
    enColPart->SelectByPoint(2, 32.5, 0);
    EnColChamfer->Add(enColPart->GetByIndex(0));
    cham->Create();


    ksEntityCollectionPtr flFaces = Part->EntityCollection(o3d_face);
    for (int i = 0; i < flFaces->GetCount(); i++)
    {
        ksEntityPtr face = flFaces->GetByIndex(i);
        ksFaceDefinitionPtr def = face->GetDefinition();
        if (def->GetOwnerEntity() == rot)
        {

            double h, r;

            def->GetCylinderParam(&h, &r);
     
            if (h == 2)
            {
                face->Putname("circle_cap");
                face->Update();
                break;
            }

        }
    }



    doc->SaveAs(L"C:\\Users\\JohnyTwoJacket\\Desktop\\крышка.m3d");
}


void createPin(Kompas6API5::KompasObjectPtr kompas) {
    Kompas6API5::ksDocument3DPtr doc;
    doc = kompas->Document3D();
    doc->Create(false, true);
    doc = kompas->ActiveDocument3D();



    kompas->Visible = true;

    ksPartPtr Part;
    Part = doc->GetPart(Kompas6Constants3D::pTop_Part);
    // штырь
    ksEntityPtr sketch = Part->NewEntity(o3d_sketch);
    ksSketchDefinitionPtr sketchDef = sketch->GetDefinition();
    sketchDef->SetPlane(Part->GetDefaultEntity(o3d_planeXOY));
    sketch->Create();
    ksDocument2DPtr doc2D = sketchDef->BeginEdit();
    

    doc2D->ksLineSeg(315, 0, 0, 0, 3);


    doc2D->ksLineSeg(-320, 0, -320, 5, 1);
    doc2D->ksLineSeg(-320, 5, -20, 5, 1);
    doc2D->ksLineSeg(-20, 5, -20, 28.5, 1);
    doc2D->ksLineSeg(-20, 28.5, -18, 28.5, 1);
    doc2D->ksLineSeg(-18, 28.5, -3, 0, 1);
    doc2D->ksLineSeg(-3, 0, -320, 0, 1);
    sketchDef->EndEdit();
    // выдавливание штыря
    ksEntityPtr rot = Part->NewEntity(o3d_bossRotated);
    ksBossRotatedDefinitionPtr rotDef = rot->GetDefinition();
    rotDef->SetSideParam(TRUE, 360);
    rotDef->directionType* (Kompas6Constants3D::dtNormal);
    rotDef->SetSketch(sketch);
    rot->Create();

    ksEntityCollectionPtr flFaces = Part->EntityCollection(o3d_face);
    ksEntityPtr face = flFaces->GetByIndex(2);
    face->Putname("circle_pin");
    face->Update();


    doc->SaveAs(L"C:\\Users\\JohnyTwoJacket\\Desktop\\штырь.m3d");
}


void createCylinder(Kompas6API5::KompasObjectPtr kompas) {
    Kompas6API5::ksDocument3DPtr doc;
    doc = kompas->Document3D();
    doc->Create(false, true);
    doc = kompas->ActiveDocument3D();



    kompas->Visible = true;

    ksPartPtr Part;
    Part = doc->GetPart(Kompas6Constants3D::pTop_Part);
    
    ksEntityPtr sketch = Part->NewEntity(o3d_sketch);
    ksSketchDefinitionPtr sketchDef = sketch->GetDefinition();
    sketchDef->SetPlane(Part->GetDefaultEntity(o3d_planeXOY));
    sketch->Create();
    ksDocument2DPtr doc2D = sketchDef->BeginEdit();
    doc2D->ksLineSeg(0, 0, 2, 0, 3);

    doc2D->ksLineSeg(0, 5, -5, 5, 1);
    doc2D->ksLineSeg(-5, 5, -20, 28.5, 1);
    doc2D->ksLineSeg(-20, 28.5, -190, 28.5, 1);
    doc2D->ksLineSeg(-190, 28.5, -190, 5, 1);
    doc2D->ksLineSeg(-190, 5, -200, 5, 1);
    doc2D->ksLineSeg(-200, 5, -200, 30.5, 1);
    doc2D->ksLineSeg(-200, 30.5, 0, 30.5, 1);
    doc2D->ksLineSeg(0, 30.5, 0, 5, 1);
    sketchDef->EndEdit();
    // выдавливание цилиндра
    ksEntityPtr rot = Part->NewEntity(o3d_bossRotated);
    ksBossRotatedDefinitionPtr rotDef = rot->GetDefinition();
    rotDef->SetSideParam(TRUE, 360);
    rotDef->directionType* (Kompas6Constants3D::dtNormal);
    rotDef->SetSketch(sketch);
    rot->Create();

    ksEntityCollectionPtr flFaces = Part->EntityCollection(o3d_face);
    for (int i = 0; i < flFaces->GetCount(); i++)
    {
        ksEntityPtr face = flFaces->GetByIndex(i);
        ksFaceDefinitionPtr def = face->GetDefinition();
        if (def->GetOwnerEntity() == rot)
        {
           
                double h, r;
             
                def->GetCylinderParam(&h, &r);
            
                if (h == 5)
                {
                    face->Putname("circle_cylender");
                    face->Update();
                    break;
                }
            
        }
    }

    doc->SaveAs(L"C:\\Users\\JohnyTwoJacket\\Desktop\\цилиндр.m3d");

}

void createStand(Kompas6API5::KompasObjectPtr kompas) {
    Kompas6API5::ksDocument3DPtr doc;
    doc = kompas->Document3D();
    doc->Create(false, true);
    doc = kompas->ActiveDocument3D();

    kompas->Visible = true;

    ksPartPtr Part;
    Part = doc->GetPart(Kompas6Constants3D::pTop_Part);

    ksEntityPtr sketch = Part->NewEntity(o3d_sketch);
    ksSketchDefinitionPtr sketchDef = sketch->GetDefinition();
    sketchDef->SetPlane(Part->GetDefaultEntity(o3d_planeXOZ));
    sketch->Create();
    ksDocument2DPtr doc2D = sketchDef->BeginEdit();
    doc2D->ksArcBy3Points(-30, 50, -40, 60, -50, 50, 1);
    doc2D->ksLineSeg(-50, 50, -50, -50, 1);
    doc2D->ksArcBy3Points(-50, -50, -40, -60, -30, -50, 1);
    doc2D->ksLineSeg(-30, -50, -30, 50, 1);
    doc2D->ksCircle(-40, 50, 5, 1);
    doc2D->ksCircle(-40, -50, 5, 1);


    doc2D->ksArcBy3Points(-170, 50, -160, 60, -150, 50, 1);
    doc2D->ksLineSeg(-150, 50, -150, -50, 1);
    doc2D->ksArcBy3Points(-150, -50, -160, -60, -170, -50, 1);
    doc2D->ksLineSeg(-170, -50, -170, 50, 1);
    doc2D->ksCircle(-160, 50, 5, 1);
    doc2D->ksCircle(-160, -50, 5, 1);

    sketchDef->EndEdit();
    // выдавливание вот этой штуки
    ksEntityPtr extr = Part->NewEntity(o3d_bossExtrusion);
    ksBossExtrusionDefinitionPtr extrDef = extr->GetDefinition();
    extrDef->SetSideParam(TRUE, etBlind, 10, 0, FALSE);
    extrDef->directionType* (Kompas6Constants3D::dtNormal);
    extrDef->SetSketch(sketch);
    extr->Create();


    ksEntityCollectionPtr flFaces = Part->EntityCollection(o3d_face);
    for (int i = 0; i < flFaces->GetCount(); i++)
    {
        ksEntityPtr face = flFaces->GetByIndex(i);
        ksFaceDefinitionPtr def = face->GetDefinition();
        if (def->GetOwnerEntity() == extr)
        {

           
                double h, r;
              
                def->GetCylinderParam(&h, &r);
                std::cout << h << " " << r << std::endl;
                if (h < 10)
                {

                    face->Putname("circle_stand");
                    face->Update();
                    break;
                }
           


   

        }
    }

    doc->SaveAs(L"C:\\Users\\JohnyTwoJacket\\Desktop\\подставка.m3d");

}

int main()
{
    CoInitialize(NULL);
    Kompas6API5::KompasObjectPtr kompas;
    HRESULT hRes;
    hRes = kompas.GetActiveObject(L"Kompas.Application.5");
    if (FAILED(hRes)) {
        kompas.CreateInstance(L"Kompas.Application.5");
    }

    createCap(kompas);
    createPin(kompas);
    createCylinder(kompas);
    createStand(kompas);


    Kompas6API5::ksDocument3DPtr doc;
    doc = kompas->Document3D();
    doc->Create(false, false);
    doc = kompas->ActiveDocument3D();
    ksPartPtr Part = doc->GetPart(Kompas6Constants3D::pTop_Part);




    doc->SetPartFromFile(L"C:\\Users\\JohnyTwoJacket\\Desktop\\штырь.m3d", Part, VARIANT_FALSE);
    doc->SetPartFromFile(L"C:\\Users\\JohnyTwoJacket\\Desktop\\цилиндр.m3d", Part, VARIANT_FALSE);
    doc->SetPartFromFile(L"C:\\Users\\JohnyTwoJacket\\Desktop\\крышка.m3d", Part, VARIANT_FALSE);
    doc->SetPartFromFile(L"C:\\Users\\JohnyTwoJacket\\Desktop\\подставка.m3d", Part, VARIANT_FALSE);
  


    ksPartCollectionPtr partCollection = doc->PartCollection(VARIANT_TRUE);
    int x = partCollection->GetCount();
    std::cout << x;

    Part = partCollection->GetByIndex(0);
    ksEntityCollectionPtr PartCol = Part->EntityCollection(o3d_face);
    ksEntityPtr circle_pin = PartCol->GetByName("circle_pin", true, true);
  


    ksPartPtr Part2 = partCollection->GetByIndex(1);
    PartCol = Part2->EntityCollection(o3d_face);
    ksEntityPtr circle_cylender = PartCol->GetByName("circle_cylender", true, true);


    ksPartPtr Part3 = partCollection->GetByIndex(2);
    PartCol = Part3->EntityCollection(o3d_face);
    ksEntityPtr circle_cap = PartCol->GetByName("circle_cap", true, true);

    ksPartPtr Part4 = partCollection->GetByIndex(3);
    PartCol = Part4->EntityCollection(o3d_face);
    ksEntityPtr circle_stand = PartCol->GetByName("circle_stand", true, true);

    doc->AddMateConstraint(mc_Concentric, circle_cylender, circle_pin, 0, 0, 0);
    doc->AddMateConstraint(mc_Concentric, circle_cylender, circle_cap, 0, 0, 0);
    doc->AddMateConstraint(mc_Distance, circle_cylender, circle_stand, 0, 0, 20);

 
    CoUninitialize();

}

